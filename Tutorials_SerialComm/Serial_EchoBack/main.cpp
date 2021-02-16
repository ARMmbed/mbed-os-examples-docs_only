/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

static BufferedSerial pc(USBTX, USBRX);

int main()
{
    char msg[] = "Echoes back to the screen anything you type\n";
    char buff;
    pc.write(msg, sizeof(msg));
    while (1) {
        pc.read(&buff, 1);
        pc.write(&buff, 1);
    }
}