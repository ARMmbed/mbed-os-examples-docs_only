/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

BufferedSerial pc(USBTX, USBRX);

int main()
{
    pc.set_baud(9600);
    char msg[] = "Hello World!\r\n";
    pc.write(msg, sizeof(msg));
}
