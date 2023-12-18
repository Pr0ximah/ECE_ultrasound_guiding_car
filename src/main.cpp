#include <Arduino.h>

#include "chassis.h"
// #include "screen.h"
#include "usSensor.h"

void setup() {
    // Chassis chassis;
    // while (true) {
    //     if (Serial.readString() == "START") {
    //         // chassis.goForward(30, 10);
    //         chassis.rotate(50, false);
    //         delay(1000);
    //         chassis.stop();
    //     }
    //     delay(10);
    // }
    // Screen screen;
    // screen.print("hello");
    // Serial.begin(9600);
    // String str;
    // while (true) {
    //     if ((str = Serial.readString()) != "") {
    //         screen.print(str);
    //     }
    //     delay(10);
    // }
    Serial.begin(9600);
    US_Sensor us = US_Sensor(6);
    while (true) {
        us.update();
        Serial.println(us.getDistance());
        delay(10);
    }
}

void loop() {}