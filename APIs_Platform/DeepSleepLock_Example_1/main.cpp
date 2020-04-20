/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono_literals;

InterruptIn button(BUTTON1);
DigitalOut led(LED1);

void toggle()
{
    led = !led;
}

int main()
{
    button.rise(&toggle);
    button.fall(&toggle);

    // Lock deep sleep to decrease interrupt latency
    // at the expense of high power consumption
    DeepSleepLock lock;

    while (1) {
        // Wait and let interrupts take care of the rest
        ThisThread::sleep_for(1s);
    }
}
