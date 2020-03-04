/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalInOut mypin(LED1);

int main()
{
    // check that mypin object is initialized and connected to a pin
    if (mypin.is_connected()) {
        printf("mypin is initialized and connected!\n\r");
    }

    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
    mypin.mode(PullNone);

    while (1) {
        // write to pin as output
        mypin.output();
        mypin = !mypin; // toggle output
        ThisThread::sleep_for(500);

        // read from pin as input
        mypin.input();
        printf("mypin.read() = %d \n\r", mypin.read());
        ThisThread::sleep_for(500);
    }
}
