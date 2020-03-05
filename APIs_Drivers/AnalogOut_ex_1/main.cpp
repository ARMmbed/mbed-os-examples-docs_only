/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

const double pi = 3.141592653589793238462;
const double amplitude = 0.5f;
const double offset = 65535 / 2;

// The sinewave is created on this pin
// Adjust analog output pin name to your board spec.
AnalogOut aout(A5);

int main()
{
    double rads = 0.0;
    uint16_t sample = 0;

    while (1) {
        // sinewave output
        for (int i = 0; i < 360; i++) {
            rads = (pi * i) / 180.0f;
            sample = (uint16_t)(amplitude * (offset * (cos(rads + pi))) + offset);
            aout.write_u16(sample);
        }
    }
}
