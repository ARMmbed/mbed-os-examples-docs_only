/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut myled(LED1);

int main()
{
    // check that myled object is initialized and connected to a pin
    if (myled.is_connected()) {
        printf("myled is initialized and connected!\n\r");
    }

    // Blink LED
    while (1) {
        myled = 1;          // set LED1 pin to high
        printf("myled = %d \n\r", (uint8_t)myled);
        ThisThread::sleep_for(500);

        myled.write(0);     // set LED1 pin to low
        printf("myled = %d \n\r", myled.read());
        ThisThread::sleep_for(500);
    }
}
