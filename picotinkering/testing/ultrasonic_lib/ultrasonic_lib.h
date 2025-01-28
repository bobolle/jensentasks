#ifndef ultrasonic_lib_h
#define ultrasonic_lib_h

void setupPins(uint triggerPin, uint echoPin);
int getCM(uint triggerPin, uint echoPin);

#endif
