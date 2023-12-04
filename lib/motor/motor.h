#ifndef MOTOR_H
#define MOTOR_H
#include "constDef.h"

class motor {
private:
    int portA, portB;
public:
    motor(int _A, int _B);
    void spin(double percent, dir dir);
};

#endif // MOTOR_H