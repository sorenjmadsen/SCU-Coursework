#include "wiced.h"

#define I2C_ADDRESS (0x42)
#define RETRIES     (1)
#define DISABLE_DMA (WICED_TRUE)
#define NUM_MESSAGES (1)

#define CONTROL_REG (0x05)
#define LED_REG     (0x04)

volatile wiced_bool_t buttonPress = WICED_FALSE;
volatile wiced_bool_t direction = WICED_FALSE;

void button_isr(void * arg){
    buttonPress = WICED_TRUE;
}

void button_isr2 (void * arg){
    static wiced_bool_t led2 = WICED_FALSE;
        if (led2 == WICED_TRUE) {
            wiced_gpio_output_low(WICED_LED1);
            led2 = WICED_FALSE;
        }
        else {
            wiced_gpio_output_high(WICED_LED1);
            led2 = WICED_TRUE;
        }
}

void application_start(){
    wiced_init();

    wiced_gpio_input_irq_enable(WICED_SH_MB1, IRQ_TRIGGER_FALLING_EDGE, button_isr, NULL);

    const wiced_i2c_device_t i2cDevice = {
            .port = WICED_I2C_2, //The slave address is 0x42
            .address = I2C_ADDRESS, //The address of the device on the I2C bus
            .address_width = I2C_ADDRESS_WIDTH_7BIT,
            .speed_mode = I2C_STANDARD_SPEED_MODE
    };

    wiced_i2c_init(&i2cDevice); //Initializes an I2C interface
    uint8_t tx_buffer[] = {0, 0};
    wiced_i2c_message_t msg;
    wiced_i2c_init_tx_message(&msg, tx_buffer, sizeof(tx_buffer), RETRIES, DISABLE_DMA);

    tx_buffer[0] = CONTROL_REG;
    tx_buffer[1] = 0x01;
    wiced_i2c_transfer(&i2cDevice, &msg, NUM_MESSAGES);
    tx_buffer[0] = LED_REG; /* Set offset for the LED register (0x04) */

    while ( 1 )
    {
        if (direction) {
            tx_buffer[1] = tx_buffer[1] >> 1; /* Shift to the next LED */
                                    if (tx_buffer[1] < 0x01) /* Reset after turning on LED3 */
                                    {
                                        tx_buffer[1] = 0x08;
                                    }
                                    /* Send new I2C data */
                                    wiced_i2c_transfer(&i2cDevice, &msg, NUM_MESSAGES);
        }
        else {
            tx_buffer[1] = tx_buffer[1] << 1; /* Shift to the next LED */
                        if (tx_buffer[1] > 0x08) /* Reset after turning on LED3 */
                        {
                            tx_buffer[1] = 0x01;
                        }
                        /* Send new I2C data */
                        wiced_i2c_transfer(&i2cDevice, &msg, NUM_MESSAGES);
        }

        if(buttonPress)
        {
            direction = direction ? WICED_FALSE : WICED_TRUE;
            buttonPress = WICED_FALSE;
        }
        wiced_rtos_delay_milliseconds(200);
    }
}
