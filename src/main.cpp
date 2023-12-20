#include <Arduino.h>

#include "chassis.h"
// #include "screen.h"
#include "motor.h"

void setup() {
    // Chassis chassis;
    // while (true) {
    //     chassis.goForward(40, 0);
    //     // chassis.rotate(50, false);
    //     delay(1000);
    //     chassis.stop();
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

    Chassis *c = Chassis::getInstance();
    while (true) {
        c->update();
        delay(30);
        c->refreshFlagL = true;
        c->refreshFlagR = true;
    }
}

void loop() {}