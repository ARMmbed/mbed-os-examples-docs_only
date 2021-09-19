/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

BusOut myleds(LED1, LED2, LED3);

int main()
{
    while (1) {
        for (int i = 0; i < 16; i++) {
            myleds = i;
            ThisThread::sleep_for(250);
        }
    }
}
