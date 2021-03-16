/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

LowPowerTicker flipper;
DigitalOut led1(LED1);

void flip()
{
    led1 = !led1;
}

int main()
{
    led1 = 1;
    flipper.attach(&flip, 2s); // the address of the function to be attached (flip) and the interval (2 seconds)

    while (1) {
        ThisThread::sleep_for(200ms);
    }
}
