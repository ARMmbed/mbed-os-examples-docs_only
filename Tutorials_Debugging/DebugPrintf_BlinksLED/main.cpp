/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut led1(LED1);

int main()
{
    while (true) {
        led1 = !led1;

        // Print something over the serial connection
        printf("Blink! LED is now %d\r\n", led1.read());
        ThisThread::sleep_for(500);
    }
}
