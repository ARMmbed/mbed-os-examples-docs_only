#include "mbed.h"

DigitalIn button(BUTTON1); // Change to match your board
DigitalOut led(LED1);

#define BUTTON_PRESS 0

int main()
{
    while (1) {
        if (BUTTON_PRESS == button) {
            led = !led;
            ThisThread::sleep_for(1s);
        }
    }
}
