/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.
PwmOut led(LED2);

int main()
{
    // specify period first, then everything else
    led.period(4.0f);  // 4 second period
    led.pulsewidth(2); // 2 second pulse (on)
    while (1);         // led flashing
}
