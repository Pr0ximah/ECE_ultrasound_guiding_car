#include "screen.h"

Screen::Screen() {
    display.begin();
    display.setContrast(60);
    display.clearDisplay();
}

void Screen::setCur(int row, int col) {
    cursor[0] = row;
    cursor[1] = col;
}

void Screen::print(String str) {
    display.setCursor(cursor[0], cursor[1]);
    display.clearDisplay();
    display.println(str);
    display.display();
}

void Screen::clear() {
    display.clearDisplay();
}