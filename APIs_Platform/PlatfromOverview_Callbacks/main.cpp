/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Create a serial object
static UnbufferedSerial serial(USBTX, USBRX);
char *c = new char[1];

// A function that echoes any received data back
void echo()
{
    while (serial.readable()) {
        serial.read(c, sizeof(c));
        serial.write(c, sizeof(c));
    }
}

int main(void)
{
    // Call our function echo whenever the serial line receives data
    serial.attach(&echo, UnbufferedSerial::RxIrq);
}
