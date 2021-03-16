/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBSerial.h"

using namespace std::chrono_literals;

//Virtual serial port over USB
USBSerial serial;

int main(void)
{
    while (1) {
        serial.printf("I am a virtual serial port\r\n");
        ThisThread::sleep_for(1s);
    }
}
