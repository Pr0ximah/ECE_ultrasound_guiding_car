#include "motor.h"
#include <Arduino.h>

motor::motor(int _A, int _B) {
    portA = _A;
    portB = _B;
    pinMode(portA, OUTPUT);
    pinMode(portB, OUTPUT);    
}

void motor::spin(double percent, dir dir) {
    if (percent < 0) {
        if (dir == forward) {
            dir = reverse;
        } else {
            dir = forward;
        }
        percent = -percent;
    }
    if (percent > 100) {
        percent = 100;
    }
    digitalWrite(portB, dir);
    analogWrite(portA, percent / 100 * 255);
}