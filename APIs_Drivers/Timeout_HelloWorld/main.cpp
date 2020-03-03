/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

Timeout flipper;
DigitalOut led1(LED1);
DigitalOut led2(LED2);

void flip()
{
    led2 = !led2;
}

int main()
{
    led2 = 1;
    flipper.attach(&flip, 2.0); // setup flipper to call flip after 2 seconds

    // spin in a main loop. flipper will interrupt it to call flip
    while (1) {
        led1 = !led1;
        ThisThread::sleep_for(200);
    }
}
