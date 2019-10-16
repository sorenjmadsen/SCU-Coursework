#include "wiced.h"
#define PWM_PIN WICED_PWM_5
#define I2C_ADDRESS (0x42)
#define RETRIES     (1)
#define DISABLE_DMA (WICED_TRUE)
#define NUM_MESSAGES (1)

#define TEMPERATURE_REG (0x07)

void application_start( )
{
    float duty_cycle = 0.0;
    wiced_init(); /* Initialize the WICED device */

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



    // Need to de-init the GPIO if it is already set to drive the LED
    wiced_gpio_deinit(WICED_SH_LED1);
    while ( 1 )
    {
        wiced_i2c_transfer(&i2cDevice, &msg, NUM_MESSAGES);
        wiced_pwm_init(PWM_PIN, 1000, duty_cycle);
        wiced_pwm_start(PWM_PIN);
        duty_cycle = rx_buffer.light / 180;
        WPRINT_APP_INFO(("Temperature: %.1f\t Humidity: %.1f\t Light:%.1f\t POT: %.1f\n", rx_buffer.temp, rx_buffer.humidity, rx_buffer.light, rx_buffer.pot));
        wiced_rtos_delay_milliseconds( 20 );
    }
}
