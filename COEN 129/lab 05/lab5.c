#include "wiced.h"

void button_isr(void * arg){
    static wiced_bool_t led1 = WICED_FALSE;
    if (led1 == WICED_TRUE) {
        wiced_gpio_output_low(WICED_LED2);
        led1 = WICED_FALSE;
    }
    else {
        wiced_gpio_output_high(WICED_LED2);
        led1 = WICED_TRUE;
    }
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

    wiced_gpio_input_irq_enable(WICED_SH_MB0, IRQ_TRIGGER_FALLING_EDGE, button_isr, NULL);
    wiced_gpio_input_irq_enable(WICED_SH_MB1, IRQ_TRIGGER_FALLING_EDGE, button_isr2, NULL);

    while (1){

    }
}
