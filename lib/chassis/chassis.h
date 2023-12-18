#ifndef _CHASSIS_H
#define _CHASSIS_H
#include "motor.h"
#include "constDef.h"
#include "screen.h"
#include "usSensor.h"
#include <Arduino.h>

class Chassis {
private:
    motor motorL = motor(PortMotorA1, PortMotorB1);
    motor motorR = motor(PortMotorA2, PortMotorB2);
    Screen screen;
    US_Sensor usl = US_Sensor(usl_pin);
    US_Sensor usr = US_Sensor(usr_pin);

public:
    Chassis() {
        Serial.begin(9600);
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
};

#endif // _CHASSIS_H