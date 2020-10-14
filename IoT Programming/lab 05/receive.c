#include "wiced.h"
volatile wiced_bool_t newPress = WICED_FALSE;


void application_start(){
    char receiveChar;
    uint32_t expected_data_size = 1;
    wiced_init();
    #define RX_BUFFER_SIZE (5)
    wiced_ring_buffer_t rx_buffer;
    uint8_t rx_data[RX_BUFFER_SIZE];

    ring_buffer_init(&rx_buffer, rx_data, RX_BUFFER_SIZE);

    wiced_uart_config_t uart_config =
    {
            .baud_rate = 115200,
            .data_width = DATA_WIDTH_8BIT,
            .parity = NO_PARITY,
            .stop_bits = STOP_BITS_1,
            .flow_control = FLOW_CONTROL_DISABLED
    };

    wiced_uart_init(WICED_UART_1, &uart_config, &rx_buffer);

    while (1){
        if (wiced_uart_receive_bytes(WICED_UART_1, &receiveChar, &expected_data_size, WICED_NEVER_TIMEOUT) == WICED_SUCCESS){
            if (receiveChar == '1') wiced_gpio_output_low(WICED_LED1);
            if (receiveChar == '0') wiced_gpio_output_high(WICED_LED1);
        }
    }
}
