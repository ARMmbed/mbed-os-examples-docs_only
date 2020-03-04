/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

SPISlave device(D12, D11, D13, D10); // mosi, miso, sclk, ssel

int main()
{
    device.reply(0x00);              // Prime SPI with first reply
    while (1) {
        if (device.receive()) {
            int v = device.read();   // Read byte from master
            v = (v + 1) % 0x100;     // Add one to it, modulo 256
            device.reply(v);         // Make this the next reply
        }
    }
}
