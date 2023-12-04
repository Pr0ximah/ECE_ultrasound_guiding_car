#include <Arduino.h>
// #include "constDef.h"
#include "motor.h"

motor m1(10, 9);
motor m2(11, 12);

void setup() {
    // pinMode(10, OUTPUT);
    // pinMode(9, OUTPUT);
    // pinMode(11, OUTPUT);
    // pinMode(12, OUTPUT);
    // digitalWrite(9, LOW);
    // analogWrite(10, 255);
    // digitalWrite(11, HIGH);
    // analogWrite(12, 255);// 
}

void loop() {
    m1.spin(60, reverse);
    m2.spin(30, forward);
    delay(10);
}