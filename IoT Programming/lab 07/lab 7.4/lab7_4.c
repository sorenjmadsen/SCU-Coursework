#include "wiced.h"

#define THREAD_PRIORITY (10)
#define THREAD_STACK_SIZE (1024)

#define I2C_ADDRESS (0x42)
#define RETRIES     (1)
#define DISABLE_DMA (WICED_TRUE)
#define NUM_MESSAGES (1)

#define TEMPERATURE_REG (0x07)

#define RX_BUFFER_SIZE (16)
static wiced_bool_t flag = WICED_FALSE;

static wiced_thread_t ledThreadHandle, tempThreadHandle;
static wiced_semaphore_t semaphoreLED, semaphoreTemp;

wiced_timer_t timerHandle;

void flagset() {
    flag = WICED_FALSE;
    wiced_rtos_stop_timer(&timerHandle);
}

void button_isr(void* arg) {
    if (!flag) {
        flag = WICED_TRUE;
        wiced_rtos_set_semaphore(&semaphoreLED); /* Set the semaphore */
        wiced_rtos_set_semaphore(&semaphoreTemp); /* Set the semaphore */
        /* Initialize and start a timer */

        wiced_rtos_start_timer(&timerHandle);
    }
}

void ledThread(wiced_thread_arg_t arg) // The thread function for LED toggle
{
    static wiced_bool_t led1 = WICED_FALSE;
    while (1) {
        wiced_rtos_get_semaphore(&semaphoreLED, WICED_WAIT_FOREVER);
        while (flag) {
            if (led1 == WICED_TRUE) {
                wiced_gpio_output_low(WICED_SH_LED1);
                led1 = WICED_FALSE;
            } else {
                wiced_gpio_output_high(WICED_SH_LED1);
                led1 = WICED_TRUE;
            }
            wiced_rtos_delay_milliseconds(100);
        }

    }
}
void tempThread(wiced_thread_arg_t arg) // The thread function for LED toggle
{
    const wiced_i2c_device_t i2cDevice = {
                .port = WICED_I2C_2, //The slave address is 0x42
                .address = I2C_ADDRESS, //The address of the device on the I2C bus
                .address_width = I2C_ADDRESS_WIDTH_7BIT,
                .speed_mode = I2C_STANDARD_SPEED_MODE
    };

    wiced_i2c_init(&i2cDevice); //Initializes an I2C interface

    uint8_t tx_buffer[] = {TEMPERATURE_REG};
    wiced_i2c_message_t setOffset;
    wiced_i2c_init_tx_message(&setOffset, tx_buffer, sizeof(tx_buffer), RETRIES, DISABLE_DMA);
    wiced_i2c_transfer(&i2cDevice, &setOffset, NUM_MESSAGES);

    struct {
        float temp;
        float humidity;
        float light;
        float pot;
    } rx_buffer;
    wiced_i2c_message_t msg;
    wiced_i2c_init_rx_message(&msg, &rx_buffer, sizeof(rx_buffer), RETRIES, DISABLE_DMA);

    /* Configure and start the UART. */
    wiced_ring_buffer_t rx_buffer2;
    uint8_t rx_data[RX_BUFFER_SIZE];
    ring_buffer_init(&rx_buffer2, rx_data, RX_BUFFER_SIZE);

    wiced_uart_config_t uart_config = { .baud_rate = 115200, .data_width =
            DATA_WIDTH_8BIT, .parity = NO_PARITY, .stop_bits = STOP_BITS_1,
            .flow_control = FLOW_CONTROL_DISABLED };
    wiced_uart_init(STDIO_UART, &uart_config, &rx_buffer2); /* Setup UART */

    char buffer[16];

    while (1) {
        wiced_rtos_get_semaphore(&semaphoreTemp, WICED_WAIT_FOREVER);
        while (flag) {
            wiced_i2c_transfer(&i2cDevice, &msg, NUM_MESSAGES);
            wiced_uart_transmit_bytes(WICED_UART_1, "Temperature: ", 13);
            memset(buffer, 0, 16*sizeof(char));
            snprintf(buffer, 16, "%.1f\r\n", rx_buffer.temp);
            wiced_uart_transmit_bytes(WICED_UART_1, buffer, 16);
            wiced_rtos_delay_milliseconds(200);
        }
    }
}
void application_start() {
    wiced_init(); /* Initialize the WICED device */
    /* Setup the semaphore which will be set by the button interrupt */
    wiced_rtos_init_semaphore(&semaphoreLED);
    wiced_rtos_init_semaphore(&semaphoreTemp);
    wiced_rtos_init_timer(&timerHandle, 2000, flagset, NULL);
    /* Initialize and start LED thread */
    wiced_rtos_create_thread(&ledThreadHandle, THREAD_PRIORITY, "ledThread",
            ledThread, THREAD_STACK_SIZE, NULL);
    wiced_rtos_create_thread(&tempThreadHandle, THREAD_PRIORITY, "tempThread",
            tempThread, THREAD_STACK_SIZE, NULL);
    /* Setup button interrupt */
    wiced_gpio_input_irq_enable(WICED_SH_MB1, IRQ_TRIGGER_FALLING_EDGE,
            button_isr, NULL);
}
