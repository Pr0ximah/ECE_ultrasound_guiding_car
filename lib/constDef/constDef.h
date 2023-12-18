#ifndef _PORT_DEF_H
#define _PORT_DEF_H

// Motor Port
const int PortMotorA1 = 10;
const int PortMotorB1 = 9;
const int PortMotorA2 = 11;
const int PortMotorB2 = 12;

// Motor Direction
enum dir { forward, reverse };

// Screen Pin
const int RST = 15;
const int CE = 16;
const int DC = 17;
const int DI = 7;
const int CLK = 8;

// Ultrasound Sensor Pin
const int usl_pin = 1;
const int usr_pin = 2;

#endif  // _PORT_DEF_H