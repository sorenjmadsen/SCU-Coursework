#include "wiced.h"
#include "math.h"
#define THREAD_PRIORITY     (10)
#define THREAD_STACK_SIZE   (10000)
#define TIME                (10)
#define PER_SEC             (2)             // Don't have it result in a repeating decimal
#define TRIALS              (TIME * PER_SEC)  // Trials/sec * 60 sec

uint8_t ledToBlink = WICED_SH_LED0;
wiced_bool_t led = WICED_FALSE;
wiced_bool_t testing = WICED_FALSE;
static wiced_semaphore_t semaphore;

float mean(int * data) {
    float sum = 0.0;
    int i;
    for (i = 0; i < TRIALS; ++i) {
        sum += data[i];
    }
    return (float) (sum / TRIALS);
}

float std_dev(float mean, int * data) {
    int i;
    float diff_sum = 0.0;
    float diff;
    for (i = 0; i < TRIALS; ++i) {
        diff = data[i] - mean;
        diff_sum += diff * diff;
    }
    diff_sum /= TRIALS - 1;
    return (float) (sqrt(diff_sum));
}

void presentResults(int * rssi, int * noise) {
    float data[4];
    data[0] = mean(rssi);
    data[1] = std_dev(data[0], rssi);
    data[2] = mean(noise);
    data[3] = std_dev(data[2], noise);

    WPRINT_APP_INFO(("RSSI\t\tMean: %.2f \tStdDev: %.2f\n", data[0], data[1]));
    WPRINT_APP_INFO(("Noise\t\tMean: %.2f \tStdDev: %.2f\n", data[2], data[3]));
    testing = WICED_FALSE;
}

void collectData(void * arg) {
    while (1) {
        wiced_rtos_get_semaphore(&semaphore, WICED_WAIT_FOREVER);
        testing = WICED_TRUE;
        int rssi_meas[TRIALS];
        int noise_meas[TRIALS];
        int delayms = 1000 / PER_SEC;

        int32_t rssi, noise;

        int i;
        for (i = 0; i < TRIALS; ++i) {
            wwd_wifi_get_rssi(&rssi);
            rssi_meas[i] = rssi;
            wwd_wifi_get_noise(&noise);
            noise_meas[i] = noise;
            WPRINT_APP_INFO(
                    ("Trial: %d \tRSSI: %d \tNoise: %d\n", (i + 1), rssi, noise));
            wiced_rtos_delay_milliseconds(500);
        }
        presentResults(rssi_meas, noise_meas);
    }
}

void connectThread(wiced_thread_arg_t arg) {
    wiced_result_t connectResult;
    wiced_bool_t connected = WICED_FALSE;

    const wiced_ip_setting_t board_static =
    {
            INITIALISER_IPV4_ADDRESS(.ip_address, MAKE_IPV4_ADDRESS(10, 0, 0, 152)),
            INITIALISER_IPV4_ADDRESS(.netmask, MAKE_IPV4_ADDRESS(255, 255, 255, 0)),
            INITIALISER_IPV4_ADDRESS(.gateway, MAKE_IPV4_ADDRESS(10, 0, 0, 1))
    };

    while (connected == WICED_FALSE) {
        wiced_network_down(WICED_STA_INTERFACE);
        connectResult = wiced_network_up(WICED_STA_INTERFACE,
                WICED_USE_STATIC_IP, &board_static);
        if (connectResult == WICED_SUCCESS) {
            connected = WICED_TRUE;
            ledToBlink = WICED_SH_LED1;

        } else {
            wiced_rtos_delay_milliseconds(5000);
        }
    }
}

void button_isr(void* arg) {
    if (ledToBlink == WICED_SH_LED1 && testing == WICED_FALSE) {
        wiced_rtos_set_semaphore(&semaphore); /* Set the semaphore */
    } else {
        //WPRINT_APP_INFO(("Please wait.\n"));
    }
}

void application_start() {
    wiced_thread_t cnctThreadHandle, clctThreadHandle;
    wiced_init(); /* Initialize the WICED device */
    wiced_gpio_input_irq_enable(WICED_SH_MB1, IRQ_TRIGGER_FALLING_EDGE,
            button_isr, NULL);
    wiced_rtos_init_semaphore(&semaphore);

    wiced_rtos_create_thread(&cnctThreadHandle, THREAD_PRIORITY,
            "connectionThread", connectThread, THREAD_STACK_SIZE, NULL);
    wiced_rtos_create_thread(&clctThreadHandle, THREAD_PRIORITY,
                "collectionThread", collectData, THREAD_STACK_SIZE, NULL);

    while (1) {
        if (led == WICED_TRUE) {
            wiced_gpio_output_low(ledToBlink);
            led = WICED_FALSE;
        } else {
            wiced_gpio_output_high(ledToBlink);
            led = WICED_TRUE;
        }
        wiced_rtos_delay_milliseconds(250);
    }
}
