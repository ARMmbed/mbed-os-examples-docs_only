/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

static BufferedSerial pc(USBTX, USBRX); // tx, rx

int main()
{
    char msg[] = "Hello World!\n";
    pc.write(msg, sizeof(msg));
    while (1);
}