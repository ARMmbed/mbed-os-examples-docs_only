/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

AnalogIn input(A0);

#define NUM_SAMPLES 1024

int main()
{
    uint16_t samples[NUM_SAMPLES];

    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = input.read_u16();
        ThisThread::sleep_for(1ms);
    }

    printf("Results:\n");
    for (int i = 0; i < NUM_SAMPLES; i++) {
        printf("%d, 0x%04X\n", i, samples[i]);
    }
}
