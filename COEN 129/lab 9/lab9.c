#include "wiced.h"

#define TCP_CLIENT_STACK_SIZE   (6200)
#define SERVER_PORT             (7108)

static wiced_ip_address_t serverAddress; //Server IP address
static wiced_thread_t buttonUpdate;
static wiced_mac_t myMac; //Edge device’s (Cypress board) MAC address

/*
 buttonThreadMain:
 This function is the thread that waits for button presses and then sends the
 data via the sendData function
 This is done as a separate thread to make the code easier to copy to a
 later program. */

void processDataFromServer() {
    wiced_tcp_socket_t socket;
    // The TCP socket
    wiced_tcp_stream_t stream;
    // The TCP stream
    char sendMessage[20];
    wiced_result_t result, conStatus;

    // Open the connection to the remote server via a socket
    wiced_tcp_create_socket(&socket, WICED_STA_INTERFACE);
    wiced_tcp_bind(&socket, WICED_ANY_PORT);
    conStatus = wiced_tcp_connect(&socket, &serverAddress, SERVER_PORT, 2000);

    if (conStatus == WICED_SUCCESS)
        WPRINT_APP_INFO(("Successful connection!\n"));
    else {
        WPRINT_APP_INFO(("Failed connection!\n"));
        wiced_tcp_delete_socket(&socket);
        return;
    }

    wiced_tcp_stream_init(&stream, &socket);
    char rbuffer[30] = { 0 };

    // Main Loop: get the data and change LED
    while (1) {
        // Get the message

        // The first 27 bytes of the buffer will be sent by the server.
        // Byte 28 will stay 0 to null terminate the string
        uint32_t read_count;
        result = wiced_tcp_stream_read_with_count(&stream, rbuffer, 28, 500,
                &read_count);
        if (result == WICED_SUCCESS) {
            //WPRINT_APP_INFO(("Server Message = %s\n\n\n", rbuffer));
            if (rbuffer[2] == '0') {
                wiced_gpio_output_low((rbuffer[0] == '0') ? WICED_SH_LED0 : WICED_SH_LED1);
            } else if ((rbuffer[2]) == '1') {
                wiced_gpio_output_high(((rbuffer[0]) == '0') ? WICED_SH_LED0 : WICED_SH_LED1);
            }
            memset(&rbuffer, 3, 30);
        }


    }
}

void application_start(void) {
    wiced_init();

    const wiced_ip_setting_t board_static = {
    INITIALISER_IPV4_ADDRESS(.ip_address, MAKE_IPV4_ADDRESS(10, 0, 0, 152)),
    INITIALISER_IPV4_ADDRESS(.netmask, MAKE_IPV4_ADDRESS(255, 255, 255, 0)),
    INITIALISER_IPV4_ADDRESS(.gateway, MAKE_IPV4_ADDRESS(10, 0, 0, 1)) };

    wiced_network_up(WICED_STA_INTERFACE, WICED_USE_STATIC_IP, &board_static);
    wiced_result_t result;
    wwd_wifi_get_mac_address(&myMac, WICED_STA_INTERFACE);
    // Use DNS to find the address..
    // if you can't look it up after 5 seconds then hard code it.

    WPRINT_APP_INFO(("DNS Lookup iot server\n"));
    result = wiced_hostname_lookup("name_of_your_server", &serverAddress, 5000,
            WICED_STA_INTERFACE);
    if (result == WICED_ERROR || serverAddress.ip.v4 == 0) {
        WPRINT_APP_INFO(("Error in resolving DNS using hard coded address\n"));

        // Replace this with the IP address of the server
        SET_IPV4_ADDRESS(serverAddress, MAKE_IPV4_ADDRESS( 10, 0, 0, 69 ));
    }

    WPRINT_APP_INFO(
            ("server's IP : %u.%u.%u.%u\n\n", (uint8_t)(GET_IPV4_ADDRESS(serverAddress) >> 24), (uint8_t)(GET_IPV4_ADDRESS(serverAddress) >> 16), (uint8_t)(GET_IPV4_ADDRESS(serverAddress) >> 8), (uint8_t)(GET_IPV4_ADDRESS(serverAddress) >> 0)));
    WPRINT_APP_INFO(("MY MAC Address: "));
    WPRINT_APP_INFO(
            ("%X:%X:%X:%X:%X:%X\r\n", myMac.octet[0], myMac.octet[1], myMac.octet[2], myMac.octet[3], myMac.octet[4], myMac.octet[5]));

    wiced_rtos_create_thread(&buttonUpdate, WICED_DEFAULT_LIBRARY_PRIORITY,
            "Prepare to Receive", processDataFromServer, TCP_CLIENT_STACK_SIZE,
            0);
    WPRINT_APP_INFO(("Prepping to receive...\n"));
}
