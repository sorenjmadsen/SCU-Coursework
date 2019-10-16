#include "wiced.h"
#include "mqtt_api.h"

#define MQTT_BROKER_ADDRESS         "u-iot-coen-rpi-smadsen"
#define WICED_TOPIC                 "light/led1"
#define CLIENT_ID                   "Soren_Madsen"
#define MQTT_REQUEST_TIMEOUT        (5000)
#define MQTT_DELAY_IN_MILLISECONDS  (1000)
#define MQTT_PUBLISH_RETRY_COUNT    (3)
#define MQTT_SUBSCRIBE_RETRY_COUNT  (3)
#define MSG_ON                      "LIGHT ON-"
#define MSG_OFF                     "LIGHT OFF-"
#define DNS_RESOLVE_TRIES           (5)

static wiced_ip_address_t broker_address;
static wiced_mqtt_event_type_t received_event;
static wiced_semaphore_t event_semaphore;
static wiced_semaphore_t wake_semaphore;
static uint8_t pub_in_progress = 0;

static wiced_result_t wait_for_response(wiced_mqtt_event_type_t expected_event,
        uint32_t timeout) {
    if (wiced_rtos_get_semaphore(&event_semaphore, timeout) != WICED_SUCCESS) {
        return WICED_ERROR;
    } else {
        if (expected_event != received_event) {
            return WICED_ERROR;
        }
    }
    return WICED_SUCCESS;
}

static wiced_result_t mqtt_connection_event_cb(wiced_mqtt_object_t mqtt_object,
        wiced_mqtt_event_info_t *event) {
    static char data[30];
    switch (event->type) {
    case WICED_MQTT_EVENT_TYPE_SUBCRIBED: {
        WPRINT_APP_INFO(( "\nSubscription acknowledged!\n" ));
        received_event = event->type;
        wiced_rtos_set_semaphore(&event_semaphore);
    }
        break;
    case WICED_MQTT_EVENT_TYPE_CONNECT_REQ_STATUS:
    case WICED_MQTT_EVENT_TYPE_DISCONNECTED:
    case WICED_MQTT_EVENT_TYPE_PUBLISHED:
    case WICED_MQTT_EVENT_TYPE_UNSUBSCRIBED: {
        received_event = event->type;
        wiced_rtos_set_semaphore(&event_semaphore);
    }
        break;
    case WICED_MQTT_EVENT_TYPE_PUBLISH_MSG_RECEIVED: {
        WPRINT_APP_INFO(( "\nReceived message from broker!\n" ));
        wiced_mqtt_topic_msg_t msg = event->data.pub_recvd;
        memcpy(data, msg.data, msg.data_len);
        data[msg.data_len + 1] = '\0';
        if (!strncmp(data, "LIGHT ON", 8)) {
            wiced_gpio_output_high(WICED_SH_LED1);
            WPRINT_APP_INFO(( "LIGHT ON\n" ));
        } else {
            wiced_gpio_output_low(WICED_SH_LED1);
            WPRINT_APP_INFO(( "LIGHT OFF\n" ));
        }
    }
        break;
    default:
        break;
    }
    return WICED_SUCCESS;
}

static wiced_result_t mqtt_conn_open(wiced_mqtt_object_t mqtt_obj,
        wiced_ip_address_t *address, wiced_interface_t interface,
        wiced_mqtt_callback_t callback, wiced_mqtt_security_t *security) {

    wiced_mqtt_pkt_connect_t conninfo;
    wiced_result_t ret = WICED_SUCCESS;
    memset(&conninfo, 0, sizeof(conninfo));
    conninfo.port_number = 1883;
    conninfo.mqtt_version = WICED_MQTT_PROTOCOL_VER4;
    conninfo.clean_session = 1;
    conninfo.client_id = (uint8_t*) CLIENT_ID;
    conninfo.keep_alive = 1;
    conninfo.username = (uint8_t*) "smadsen";
    conninfo.password = (uint8_t*) "testing123";
    ret = wiced_mqtt_connect(mqtt_obj, address, interface, callback, security,
            &conninfo);

    if (ret != WICED_SUCCESS) {
        return WICED_ERROR;
    }
    if (wait_for_response(WICED_MQTT_EVENT_TYPE_CONNECT_REQ_STATUS,
    MQTT_REQUEST_TIMEOUT) != WICED_SUCCESS) {
        return WICED_ERROR;

    }
    return WICED_SUCCESS;
}

static wiced_result_t mqtt_app_subscribe(wiced_mqtt_object_t mqtt_obj,
        char *topic, uint8_t qos) {
    wiced_mqtt_msgid_t pktid;
    pktid = wiced_mqtt_subscribe(mqtt_obj, topic, qos);
    if (pktid == 0) {
        return WICED_ERROR;
    }
    if (wait_for_response(WICED_MQTT_EVENT_TYPE_SUBCRIBED, MQTT_REQUEST_TIMEOUT)
            != WICED_SUCCESS) {
        return WICED_ERROR;
    }
    return WICED_SUCCESS;
}

static wiced_result_t mqtt_app_publish(wiced_mqtt_object_t mqtt_obj,
        uint8_t qos, uint8_t *topic, uint8_t *data, uint32_t data_len) {

    wiced_mqtt_msgid_t pktid;
    pktid = wiced_mqtt_publish(mqtt_obj, topic, data, data_len, qos);
    if (pktid == 0) {
        return WICED_ERROR;
    }
    if (wait_for_response(WICED_MQTT_EVENT_TYPE_PUBLISHED, MQTT_REQUEST_TIMEOUT)
            != WICED_SUCCESS) {
        return WICED_ERROR;
    }
    return WICED_SUCCESS;
}

static wiced_result_t mqtt_conn_close(wiced_mqtt_object_t mqtt_obj) {
    if (wiced_mqtt_disconnect(mqtt_obj) != WICED_SUCCESS) {
        return WICED_ERROR;
    }
    if (wait_for_response(WICED_MQTT_EVENT_TYPE_DISCONNECTED,
    MQTT_REQUEST_TIMEOUT) != WICED_SUCCESS) {
        return WICED_ERROR;
    }
    return WICED_SUCCESS;
}

static void button_callback(void* arg) {
    if (pub_in_progress == 0) {
        pub_in_progress = 1;
        wiced_rtos_set_semaphore(&wake_semaphore);
    }
}

void application_start(void) {
    wiced_mqtt_object_t mqtt_object;
    wiced_result_t ret = WICED_SUCCESS;
    int connection_retries = 0;
    int pub_sub_retries = 0;
    int count = 0;
    int resolve_count = 0;
    char msg[30];
    wiced_init();
    /* Bring up the network interface */
    ret = wiced_network_up(WICED_STA_INTERFACE, WICED_USE_EXTERNAL_DHCP_SERVER,
    NULL);
    if (ret != WICED_SUCCESS) {
        WPRINT_APP_INFO(( "\nNot able to join the requested AP\n\n" ));
        return;
    }
    /* configure push button to publish a message */
    wiced_gpio_input_irq_enable(WICED_SH_MB1, IRQ_TRIGGER_RISING_EDGE,
            button_callback, NULL);

    /* Allocate memory for MQTT object*/
    mqtt_object = (wiced_mqtt_object_t) malloc(
    WICED_MQTT_OBJECT_MEMORY_SIZE_REQUIREMENT);
    if (mqtt_object == NULL) {
        WPRINT_APP_ERROR("Don't have memory to allocate for MQTT object...\n");
        return;
    }

    for (resolve_count = 0; resolve_count < DNS_RESOLVE_TRIES;
            resolve_count++) {
        WPRINT_APP_INFO(( "Resolving IP address of MQTT broker...\n" ));
        ret = wiced_hostname_lookup( MQTT_BROKER_ADDRESS, &broker_address,
                10000, WICED_STA_INTERFACE);
        WPRINT_APP_INFO(
                ("Resolved Broker IP: %u.%u.%u.%u\n\n", (uint8_t)(GET_IPV4_ADDRESS(broker_address) >> 24), (uint8_t)(GET_IPV4_ADDRESS(broker_address) >> 16), (uint8_t)(GET_IPV4_ADDRESS(broker_address) >> 8), (uint8_t)(GET_IPV4_ADDRESS(broker_address) >> 0)));
        if (ret == WICED_ERROR || broker_address.ip.v4 == 0) {
            WPRINT_APP_INFO(("Error in resolving DNS... Retrying...\n"));
            if (resolve_count == DNS_RESOLVE_TRIES - 1){
                WPRINT_APP_INFO(("Error: Could not resolve DNS\n"));
                return;
            }
            continue;
        }
        break;
    }
    wiced_rtos_init_semaphore(&wake_semaphore);
    wiced_mqtt_init(mqtt_object);
    wiced_rtos_init_semaphore(&event_semaphore);
    do {
        WPRINT_APP_INFO(("[MQTT] Opening connection..."));
        do {
            ret = mqtt_conn_open(mqtt_object, &broker_address,
                    WICED_STA_INTERFACE, mqtt_connection_event_cb, NULL);
            connection_retries++;
        } while ((ret != WICED_SUCCESS)
                && (connection_retries < WICED_MQTT_CONNECTION_NUMBER_OF_RETRIES));

        if (ret != WICED_SUCCESS) {
            WPRINT_APP_INFO(("Failed connection!\n"));
            break;
        }

        WPRINT_APP_INFO(("Successful connection!\n"));
        WPRINT_APP_INFO(("[MQTT] Subscribing..."));

        do {
            ret = mqtt_app_subscribe(mqtt_object, WICED_TOPIC,
                    WICED_MQTT_QOS_DELIVER_AT_MOST_ONCE);
            pub_sub_retries++;
        } while ((ret != WICED_SUCCESS)
                && (pub_sub_retries < MQTT_SUBSCRIBE_RETRY_COUNT));

        if (ret != WICED_SUCCESS) {
            WPRINT_APP_INFO((" Failed subscribing!\n"));
            return;
        }

        while (1) {
            wiced_rtos_get_semaphore(&wake_semaphore, WICED_NEVER_TIMEOUT);
            if (pub_in_progress == 1) {
                WPRINT_APP_INFO(("[MQTT] Publishing..."));
                if (count % 2) {
                    strcpy(msg, MSG_ON);
                    strcat(msg, CLIENT_ID);
                } else {
                    strcpy(msg, MSG_OFF);
                    strcat(msg, CLIENT_ID);
                }
                pub_sub_retries = 0;
                // reset pub_sub_retries to 0 before going
                // into the loop so that the next publish after a
                // failure will still work
                do {
                    ret = mqtt_app_publish(mqtt_object,
                            WICED_MQTT_QOS_DELIVER_AT_LEAST_ONCE,
                            (uint8_t*) WICED_TOPIC, (uint8_t*) msg,
                            strlen(msg));
                    pub_sub_retries++;
                } while ((ret != WICED_SUCCESS)
                        && (pub_sub_retries < MQTT_PUBLISH_RETRY_COUNT));
                if (ret != WICED_SUCCESS) {
                    WPRINT_APP_INFO((" Failed publishing!\n"));
                    break;        //break the loop and reconnect
                } else {
                    WPRINT_APP_INFO((" Successful publishing!\n"));
                }
                pub_in_progress = 0;
                count++;
            }
            wiced_rtos_delay_milliseconds(100);
        }
        pub_in_progress = 0; // Reset flag if we got a failure so that another
        // button push is needed after a failure
        WPRINT_APP_INFO(("[MQTT] Closing connection..."));
        mqtt_conn_close(mqtt_object);
        wiced_rtos_delay_milliseconds( MQTT_DELAY_IN_MILLISECONDS * 2);
    } while (1);

    wiced_rtos_deinit_semaphore(&event_semaphore);
    WPRINT_APP_INFO(("[MQTT] Deinit connection...\n"));
    ret = wiced_mqtt_deinit(mqtt_object);
    wiced_rtos_deinit_semaphore(&wake_semaphore);
    free(mqtt_object);
    mqtt_object = NULL;
    return;
}

