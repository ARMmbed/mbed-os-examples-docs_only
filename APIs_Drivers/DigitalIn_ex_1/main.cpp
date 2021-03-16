/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

DigitalIn  mypin(SW2); // change this to the button on your board
DigitalOut myled(LED1);

int main()
{
    // check mypin object is initialized and connected to a pin
    if (mypin.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }

    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
    mypin.mode(PullNone);

    // press the button and see the console / led change
    while (1) {
        printf("mypin has value : %d \n\r", mypin.read());
        myled = mypin; // toggle led based on value of button
        ThisThread::sleep_for(250ms);
    }
}
