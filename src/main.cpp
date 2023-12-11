#include <Arduino.h>

#include "chassis.h"

void setup() {
    Chassis chassis;
    while (true) {
        if (Serial.readString() == "START") {
            // chassis.goForward(30, 10);
            chassis.rotate(50, false);
            delay(1000);
            chassis.stop();
        }
        delay(10);
    }
}

void loop() {}