#include "pico/stdlib.h"
#include "ultrasonic_lib.h"

uint triggerPin = 21;
uint echoPin = 20;

int main() {
    stdio_init_all();
    setupPins(triggerPin, echoPin);

    while (1) {
        printf("Distance in cm: %d\n", getCM(triggerPin, echoPin));
        sleep_ms(1000);
    }
}
