/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Switch on an LED if any of mbed pins 21-26 is high
PortIn     p(PortA, 0x0000003F);   // p21-p26
DigitalOut ind(LED4);

int main()
{
    while (1) {
        int pins = p.read();
        if (pins) {
            ind = 1;
        } else {
            ind = 0;
        }
    }
}
