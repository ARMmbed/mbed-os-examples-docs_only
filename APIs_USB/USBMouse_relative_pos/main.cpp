#include "mbed.h"
#include "USBMouse.h"

//create mouse object
USBMouse mouse;

int main()
{
    int16_t x = 0;
    int16_t y = 0;
    int32_t radius = 10;
    int32_t angle = 0;

    while (1) {
        //will cause mouse to move in a circle
        x = cos((double)angle * 3.14 / 180.0) * radius;
        y = sin((double)angle * 3.14 / 180.0) * radius;

        //will move mouse x, y away from its previous position on the screen
        mouse.move(x, y);
        angle += 3;
        ThisThread::sleep_for(10);
    }
}
