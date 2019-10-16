#include "wiced.h"
#define THREAD_PRIORITY (10)
#define THREAD_STACK_SIZE (1024)
static wiced_thread_t ledThreadHandle;
static wiced_semaphore_t semaphoreHandle;
/* Interrupt service routine for the button */

void button_isr(void* arg) {
    wiced_rtos_set_semaphore(&semaphoreHandle); /* Set the semaphore */
}
void ledThread(wiced_thread_arg_t arg) // The thread function for LED toggle
{
    static wiced_bool_t led1 = WICED_FALSE;
    while (1) {
        wiced_rtos_get_semaphore(&semaphoreHandle, WICED_WAIT_FOREVER);
        if (led1 == WICED_TRUE) {
            wiced_gpio_output_low(WICED_SH_LED1);
            led1 = WICED_FALSE;
        } else {
            wiced_gpio_output_high(WICED_SH_LED1);
            led1 = WICED_TRUE;
        }
    }
}
void application_start() {
    wiced_init(); /* Initialize the WICED device */
    /* Setup the semaphore which will be set by the button interrupt */
    wiced_rtos_init_semaphore(&semaphoreHandle);
    /* Initialize and start LED thread */
    wiced_rtos_create_thread(&ledThreadHandle, THREAD_PRIORITY, "ledThread",ledThread, THREAD_STACK_SIZE, NULL);
    /* Setup button interrupt */
    wiced_gpio_input_irq_enable(WICED_SH_MB1, IRQ_TRIGGER_FALLING_EDGE,button_isr, NULL);
    /* No while(1) here since everything is done by the new thread. */
}
