#include "wiced.h"
#include "math.h"
#define THREAD_PRIORITY     (10)
#define THREAD_STACK_SIZE   (10000)
#define TRIALS              (3)

uint8_t ledToBlink = WICED_SH_LED0;
wiced_bool_t led = WICED_FALSE;

float mean(int * durations) {
    float sum = 0.0;
    int i;
    for (i = 0; i < TRIALS; ++i) {
        sum += durations[i];
    }
    return (float)(sum / TRIALS);
}

float std_dev(float mean, int * durations) {
    int i;
    float diff_sum = 0.0;
    float diff;
    for (i = 0; i < TRIALS; ++i) {
        diff = durations[i] - mean;
        diff_sum += diff*diff;
    }
    diff_sum /= TRIALS - 1;
    return (float)(sqrt(diff_sum));
}

void connectThread(wiced_thread_arg_t arg) {
    wiced_result_t connectResult;
    wiced_bool_t connected = WICED_FALSE;
    wiced_time_t start, end;
    int durations[TRIALS];

    const wiced_ip_setting_t board_static = {
    INITIALISER_IPV4_ADDRESS(.ip_address, MAKE_IPV4_ADDRESS(10, 0, 0, 152)),
    INITIALISER_IPV4_ADDRESS(.netmask, MAKE_IPV4_ADDRESS(255, 255, 255, 0)),
    INITIALISER_IPV4_ADDRESS(.gateway, MAKE_IPV4_ADDRESS(10, 0, 0, 1)) };

    float avg,stddev;

    int i;

    for (i = 0; i < TRIALS; ++i) {
        while (connected == WICED_FALSE) {
            wiced_network_down(WICED_STA_INTERFACE);
            wiced_time_get_time(&start);
            connectResult = wiced_network_up(WICED_STA_INTERFACE,
                    WICED_USE_STATIC_IP, &board_static);
            if (connectResult == WICED_SUCCESS) {
                connected = WICED_TRUE;
                ledToBlink = WICED_SH_LED1;

            } else {
                wiced_rtos_delay_milliseconds(5000);
            }
        }
        wiced_rtos_delay_milliseconds(5000); // Stay connected for 5 sec
        wiced_network_down(WICED_STA_INTERFACE);
        connected = WICED_FALSE;
        wiced_time_get_time(&end);
        durations[i] = end - start;
        WPRINT_APP_INFO(("Trial: %d \tDuration: %d ms\n", (i + 1), durations[i]));
    }

    avg = mean(durations);
    stddev = std_dev(avg, durations);
    WPRINT_APP_INFO(("Mean: %.2f ms \tStdDev: %.2f ms \n", avg, stddev));
}

void application_start() {
    wiced_thread_t cnctThreadHandle;
    wiced_init(); /* Initialize the WICED device */


    wiced_rtos_create_thread(&cnctThreadHandle, THREAD_PRIORITY,
            "connectionThread", connectThread, THREAD_STACK_SIZE, NULL);
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
