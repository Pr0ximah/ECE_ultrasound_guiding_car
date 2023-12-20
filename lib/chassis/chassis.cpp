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
    double vL = percent + 5.5;
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
    // Serial.println("vL: " + String(vL) + ",  vR: " + String(vR));
    motorL.spin(vL, forward);
    motorR.spin(vR, forward);
}

void Chassis::rotate(double percent, bool clockwise) {
    int coeff = (clockwise ? 1 : -1);
    motorL.spin(coeff * percent, forward);
    motorR.spin(coeff * percent, reverse);
}

void Chassis::update() {
    if (ignoredCnt > 30) {
        if (!ignoreStat) {
            ignoreStat = true;
        }
        ignoredCnt = 0;
    }
    if (ignoreStat && noignoredCnt > 30) {
        if (ignoreStat) {
            ignoreStat = false;
        }
        noignoredCnt = 0;
    }
    if (ignoreStat) {
        rotate(35, true);
        getAngleDiff();
    } else {
        double angleDiff = -getAngleDiff();
        double k = 0.2;
        // if (fabs(angleDiff) < 20) {
        //     goForward(60, 0);
        // } else {
        //     goForward(60, angleDiff * k);
        // }
    }
}

double Chassis::getAngleDiff() {
    int offset = 0;
    timeDiffLast = timeDiffCur;
    timeDiffCur = time_L - time_R;
    Serial.println(timeDiffCur);
    if (temp_cnt % 1 == 0 && (abs(timeDiffCur - timeDiffLast) < 1000)) {
        temp_cnt = 0;
        for (int i = 0; i < 9; i++) {
            timeDiff[i] = timeDiff[i + 1];
        }
        timeDiff[9] = timeDiffCur;
    }
    double avg = average(timeDiff, 10);
    if (avg > IGN_NUM) {
        if (!ignoreStat) {
            ignoredCnt++;
        }
    } else {
        if (ignoreStat) {
            noignoredCnt++;
        }
    }
    temp_cnt++;
    // Serial.println(avg + offset);
    return avg + offset;
}

void setL() {
    Chassis *c = Chassis::getInstance();
    if (c->refreshFlagL) {
        c->time_L = micros();
        c->refreshFlagL = false;
    }
}

void setR() {
    Chassis *c = Chassis::getInstance();
    if (c->refreshFlagR) {
        c->time_R = micros();
        c->refreshFlagR = false;
    }
}