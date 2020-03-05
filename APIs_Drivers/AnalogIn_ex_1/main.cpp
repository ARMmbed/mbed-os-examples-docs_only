/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

AnalogIn position(A0);
PwmOut servo(D3);

int main()
{
    // servo requires a 20ms period
    servo.period(0.020f);
    while (1) {
        // servo position determined by a pulse width between 1-2ms
        servo.pulsewidth(0.001f + 0.001f * position);
    }
}
