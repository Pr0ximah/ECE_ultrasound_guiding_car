#include "chassis.h"

#include <Arduino.h>

#include "motor.h"

double average(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

void Chassis::goForward(double percent, double angle) {
    double k = 0.03;
    double vL = percent + 3.14;
    double vR = percent;
    int diffV = k * angle * percent;
    if (diffV > 0) {
        vR = percent + diffV;
    } else if (diffV < 0) {
        vL = percent - diffV;
    }
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

void Chassis::update() {
    double angleDiff = -getAngleDiff();
    double k = 0.1;
    goForward(50, angleDiff * k);
    // goForward(50, 0);
}

double Chassis::getAngleDiff() {
    timeDiffCur = -Chassis::getInstance()->time_R;
    return timeDiffCur;
}

void setL() {
    Chassis *c = Chassis::getInstance();
    if (c->refreshFlag) {
        c->refreshFlag = false;
        c->time_R = 50;
    }
}

void setR() {
    Chassis *c = Chassis::getInstance();
    if (c->refreshFlag) {
        c->refreshFlag = false;
        c->time_R = -50;
    }
}