#ifndef _US_SENSOR_H
#define _US_SENSOR_H
const int NUM_FILTER = 10;

class US_Sensor {
private:
    int echoPin_L, echoPin_R;
    unsigned int pulseWidth[NUM_FILTER];
public:
    US_Sensor(int echoPin_L, int echoPin_R);
    double update();
};

#endif // _US_SENSOR_H