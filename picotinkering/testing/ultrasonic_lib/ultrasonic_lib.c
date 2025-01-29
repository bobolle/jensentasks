#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

int timeout = 26100;

void setupPins(uint triggerPin, uint echoPin) {
    gpio_init(triggerPin);
    gpio_init(echoPin);
    gpio_set_dir(triggerPin, GPIO_OUT);
    gpio_set_dir(echoPin, GPIO_IN);
}

uint64_t getPulse(uint triggerPin, uint echoPin) {
    // send pulse
    gpio_put(triggerPin, 1);
    sleep_us(10);
    gpio_put(triggerPin, 0);

    uint64_t width = 0;

    while (gpio_get(echoPin) == 0) { 
        tight_loop_contents();
    }

    // start time
    absolute_time_t startTime = get_absolute_time();

    while (gpio_get(echoPin) == 1) {
        width++;
        sleep_us(1);

        // return 0 if out of range
        if (width > timeout) {
            return 0;
        }
    }

    // end time
    absolute_time_t endTime = get_absolute_time();

    return absolute_time_diff_us(startTime, endTime);

}

int getCM(uint triggerPin, uint echoPin) {
    uint64_t pulseLength = getPulse(triggerPin, echoPin);

    // budget calculation
    return pulseLength / 29 / 2;
}
