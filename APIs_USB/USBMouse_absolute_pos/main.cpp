/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBMouse.h"

using namespace std::chrono_literals;

//setup mouse to be absolute
USBMouse mouse(true, ABS_MOUSE);

#include <math.h>

int main(void)
{
    uint16_t x_center = (X_MAX_ABS - X_MIN_ABS) / 2;
    uint16_t y_center = (Y_MAX_ABS - Y_MIN_ABS) / 2;
    uint16_t x_screen = 0;
    uint16_t y_screen = 0;

    uint32_t x_origin = x_center;
    uint32_t y_origin = y_center;
    uint32_t radius = 5000;
    uint32_t angle = 0;

    while (1) {
        x_screen = x_origin + cos((double)angle * 3.14 / 180.0) * radius;
        y_screen = y_origin + sin((double)angle * 3.14 / 180.0) * radius;

        //x_screen, y_screen will be the mouse's position on the screen
        mouse.move(x_screen, y_screen);
        angle += 3;
        ThisThread::sleep_for(10ms);
    }
}
