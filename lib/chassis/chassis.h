#ifndef _CHASSIS_H
#define _CHASSIS_H
#include "motor.h"
#include "constDef.h"
#include "screen.h"
#include "usSensor.h"
#include <Arduino.h>

void setL();
void setR();

class Chassis {
private:
    motor motorL = motor(PortMotorA1, PortMotorB1);
    motor motorR = motor(PortMotorA2, PortMotorB2);
    Screen screen;
    bool ignoreStat = false;
    int timeDiff[10];
    int ignoredCnt = 0;
    int noignoredCnt = 0;
    int temp_cnt = 0;
    int timeDiffCur = 0;
    int timeDiffLast = 0;

public:
    unsigned long long time_L;
    unsigned long long time_R;
    bool refreshFlagL;
    bool refreshFlagR;

    Chassis() {
        Serial.begin(9600);
        pinMode(2, INPUT);
        pinMode(3, INPUT);
        attachInterrupt(0, setL, FALLING); // D2
        attachInterrupt(1, setR, FALLING); // D3
        for (int i = 0; i < 10; i++) {
            timeDiff[i] = 0;
        }
    }

    void stop() {
        motorL.spin(0, forward);
        motorR.spin(0, forward);
    }

    /// @param percent - 速度百分比，正值
    /// @param angle - 附加旋转角度，逆时针为正
    void goForward(double percent, double angle);
    
    /// @param percent - 速度百分比，正值
    /// @param clockwise - 是否顺时针
    void rotate(double percent, bool clockwise);

    /// @brief 更新所有状态信息
    void update();

    static Chassis *getInstance() {
        static Chassis *c = nullptr;
        if (!c) {
            c = new Chassis;
        }
        return c;
    }

    double getAngleDiff();
};

#endif // _CHASSIS_H