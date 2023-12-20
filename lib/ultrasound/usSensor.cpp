#include "usSensor.h"

#include <Arduino.h>
#include <math.h>

#include "constDef.h"

double average(unsigned int arr[], int n) {
    unsigned int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

US_Sensor::US_Sensor(int _echoPin_L, int _echoPin_R) {
    echoPin_L = _echoPin_L;
    echoPin_R = _echoPin_R;
    pinMode(echoPin_L, INPUT);
    pinMode(echoPin_R, INPUT);
}

double US_Sensor::update() {
    // 屏蔽高信号，从均为LOW开始检测
    while (digitalRead(echoPin_L) || digitalRead(echoPin_R)) {
        continue;
    }

    bool flag = true;
    int startTime = millis();
    int intL = -1;
    int intR = -1;
    while (flag && ((millis() - startTime) < JUMP_T)) {
        bool L = digitalRead(echoPin_L);
        bool R = digitalRead(echoPin_R);
        if (L) {
            Serial.println("L");
            Serial.println("R");
            intL = micros();
            while (true) {
                bool R = digitalRead(echoPin_R);
                intR = micros();
                if (R) {
                    flag = false;
                    break;
                }
            }
        } else if (R) {
            Serial.println("R");
            intR = micros();
            while (true) {
                bool L = digitalRead(echoPin_L);
                if (L) {
                    intL = micros();
                    flag = false;
                    break;
                }
            }
        }
    }
    if (intL == -1 || intR == -1) {
        return IGN_NUM;
    } else if (abs(intL - intR) < 0) {
        return 0;
    } else {
        return intL - intR;
    }
}