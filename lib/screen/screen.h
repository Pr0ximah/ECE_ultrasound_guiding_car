#ifndef _SCREEN_H
#define _SCREEN_H
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "constDef.h"

class Screen {
private:
    Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DI, DC, CE, RST);
    int cursor[2];
public:
    Screen();
    void setCur(int row, int col);
    void print(String str);
    void clear();
    // void update();
};

#endif // _SCREEN_H