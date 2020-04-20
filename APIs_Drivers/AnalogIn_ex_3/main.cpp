/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

// Initialize a pins to perform analog input and digital output functions
AnalogIn   ain(A0);
DigitalOut dout(LED1);

int main(void)
{
    while (1) {
        // test the voltage on the initialized analog pin
        //  and if greater than 0.3 * VCC set the digital pin
        //  to a logic 1 otherwise a logic 0
        if (ain > 0.3f) {
            dout = 1;
        } else {
            dout = 0;
        }

        // print the percentage and 16 bit normalized values
        printf("percentage: %3.3f%%\n", ain.read() * 100.0f);
        printf("normalized: 0x%04X \n", ain.read_u16());
        ThisThread::sleep_for(200ms);
    }
}
