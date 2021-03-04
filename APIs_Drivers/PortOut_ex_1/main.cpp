/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

// Toggle all four LEDs
// LED1 = P1.18  LED2 = P1.20  LED3 = P1.21  LED4 = P1.23
#define LED_MASK 0x00B40000

PortOut ledport(PortA, LED_MASK);

int main()
{
    while (1) {
        ledport = LED_MASK;
        ThisThread::sleep_for(1s);
        ledport = 0;
        ThisThread::sleep_for(1s);
    }
}
