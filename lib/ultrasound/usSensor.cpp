#include "usSensor.h"

#include <Arduino.h>

double average(unsigned int arr[], int n) {
    unsigned int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

US_Sensor::US_Sensor(int _echoPin) {
    echoPin = _echoPin;
    pinMode(echoPin, INPUT);
}

void US_Sensor::update() {
    unsigned int val = pulseIn(echoPin, HIGH);
    if (val >= 20) {
        for (int i = 0; i < NUM_FILTER - 1; i++) {
            pulseWidth[i] = pulseWidth[i + 1];
        }
        pulseWidth[NUM_FILTER - 1] = val;
    }
}

double US_Sensor::getDistance() { return average(pulseWidth, NUM_FILTER); }