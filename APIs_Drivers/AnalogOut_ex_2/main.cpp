/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(A5);
DigitalOut dout(LED1);

int main(void)
{
    while (1) {
        // change the voltage on the digital output pin by 0.1 * VCC
        //  and print what the measured voltage should be (assuming VCC = 3.3v)
        for (float i = 0.0f; i < 1.0f; i += 0.1f) {
            aout = i;
            printf("aout = %1.2f volts\n", aout.read() * 3.3f);
            // turn on the led if the voltage is greater than 0.5f * VCC
            dout = (aout > 0.5f) ? 1 : 0;
            ThisThread::sleep_for(1s);
        }
    }
}
