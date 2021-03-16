/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBKeyboard.h"

USBKeyboard key;

using namespace std::chrono_literals;

int main(void)
{
    while (1) {
        key.printf("Hello World\r\n");
        ThisThread::sleep_for(1s);
    }
}
