/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBCDC.h"

using namespace std::chrono_literals;

USBCDC cdc;

int main(void)
{

    while (1) {
        char msg[] = "Hello world\r\n";
        cdc.send((uint8_t *)msg, strlen(msg));
        ThisThread::sleep_for(1s);
    }
}
