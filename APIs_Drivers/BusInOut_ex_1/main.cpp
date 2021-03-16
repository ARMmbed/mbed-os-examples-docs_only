/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

BusInOut pins(D0, D1, D2); // Change these pins to buttons on your board.

int main()
{
    while (1) {
        pins.output();
        pins = 0x3;
        ThisThread::sleep_for(1s);
        pins.input();
        ThisThread::sleep_for(1s);
        if (pins == 0x6) {
            printf("Hello!\n");
        }
    }
}
