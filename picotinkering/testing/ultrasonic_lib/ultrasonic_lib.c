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
    gpio_put(triggerPin, 1);
    sleep_us(10);
    gpio_put(triggerPin, 0);

    uint64_t width = 0;

    while (gpio_get(echoPin) == 0) { 
        tight_loop_contents();
    }

    absolute_time_t startTime = get_absolute_time();

    while (gpio_get(echoPin) == 1) {
        width++;
        sleep_us(1);
        if (width > timeout) {
            return 0;
        }
    }

    absolute_time_t endTime = get_absolute_time();

    return absolute_time_diff_us(startTime, endTime);

}

int getCM(uint triggerPin, uint echoPin) {
    uint64_t pulseLength = getPulse(triggerPin, echoPin);
    return pulseLength / 29 / 2;
}
