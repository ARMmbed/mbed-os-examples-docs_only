/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut heartbeat(LED1);

int main()
{
    while (1) {
        heartbeat = 1;
        ThisThread::sleep_for(500);
        heartbeat = 0;
    }
}
