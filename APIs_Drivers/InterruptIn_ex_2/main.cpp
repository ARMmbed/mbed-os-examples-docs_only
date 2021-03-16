/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

InterruptIn button(SW2);
DigitalOut led(LED1);
DigitalOut flash(LED4);

void flip()
{
    led = !led;
}

int main()
{
    button.rise(&flip);  // attach the address of the flip function to the rising edge
    while (1) {          // wait around, interrupts will interrupt this!
        flash = !flash;
        ThisThread::sleep_for(250ms);
    }
}
