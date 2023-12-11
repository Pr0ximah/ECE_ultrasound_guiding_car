#include "chassis.h"
#include "motor.h"

#include <Arduino.h>

void Chassis::goForward(double percent, double angle) {
    double k = 0.03;
    int diffV = k * angle * percent;
    double vL = percent - diffV / 2;
    double vR = percent + diffV / 2;
    if (vL > 100) {
        double coeff = 100 / vL;
        vL = 100;
        vR = vR * coeff;
    }
    if (vR > 100) {
        double coeff = 100 / vR;
        vR = 100;
        vL = vL * coeff;
    }
    if (vL < 25) {
        double coeff = 25 / vL;
        vL = 25;
        vR = vR * coeff;
    }
    if (vR < 25) {
        double coeff = 25 / vL;
        vL = 25;
        vR = vR * coeff;
    }
    Serial.println("vL: " + String(vL) + ",  vR: " + String(vR));
    motorL.spin(vL, forward);
    motorR.spin(vR, forward);
}


void Chassis::rotate(double percent, bool clockwise) {
    int coeff = (clockwise ? 1 : -1);
    motorL.spin(coeff * percent, forward);
    motorR.spin(coeff * percent, reverse);
}