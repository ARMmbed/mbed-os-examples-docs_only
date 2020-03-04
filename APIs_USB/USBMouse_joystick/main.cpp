/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBMouse.h"

USBMouse mouse;
// x and y axis of the joystick
AnalogIn   ainx(A0);
AnalogIn   ainy(A1);
int16_t a_inx;
int16_t a_iny;

int main()
{
    int16_t x = 0;
    int16_t y = 0;

    while (1) {
        // reads x and y values from the joystick
        a_inx = (int16_t)(ainy.read() * 100.0);
        a_iny = (int16_t)(ainx.read() * 100.0);

        // prints x and y values to serial monitor
        printf("X: %u\r\n", a_inx);
        printf("Y: %u\r\n", a_iny);

        // move position of mouse right
        if (a_inx > 52) {
            x = (x - (50 - a_inx)) / 3;
        }
        // move position of mouse left
        else if (a_inx < 47) {
            x = (a_inx - 50) / 2;
        }
        // keeps mouse stationary in x-axis
        else {
            x = 0;
        }
        // move position of mouse down
        if (a_iny > 52 && a_iny != 99) {
            y = (y - (50 - a_iny)) / 3;
        }
        // move position of mouse up
        else if (a_iny < 47) {
            y = (a_iny - 50) / 2;
        }
        // keeps mouse stationary in y-axis
        else {
            y = 0;
        }
        // if button is pressed, a_iny will be 99
        // performs mouse left click
        if (a_iny == 99) {
            //click
            mouse.click(MOUSE_LEFT);
            ThisThread::sleep_for(400);
        }
        // moves mouse to specified x, y coordinates on screen
        mouse.move(x, y);
        ThisThread::sleep_for(1);
    }
}
