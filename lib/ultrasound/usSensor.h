#ifndef _US_SENSOR_H
#define _US_SENSOR_H
const int NUM_FILTER = 80;

class US_Sensor {
private:
    int echoPin;
    unsigned int pulseWidth[NUM_FILTER];
public:
    US_Sensor(int echoPin);
    void update();
    double getDistance();
};

#endif // _US_SENSOR_H