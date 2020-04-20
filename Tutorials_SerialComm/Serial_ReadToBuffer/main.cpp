/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

// Create a serial object
static BufferedSerial pc(USBTX, USBRX);

int main(void)
{
    char buffer[10] = {};
    while (1) {
        if (pc.readable()) {
            ThisThread::sleep_for(100ms);
            pc.read(buffer, 10);
            printf("I got '%s'\n", buffer);
        }
    }
}
