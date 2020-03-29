/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

static BufferedSerial pc(USBTX, USBRX);
static BufferedSerial uart(D1, D0);

DigitalOut pc_activity(LED1);
DigitalOut uart_activity(LED2);

int main()
{
    char *pc2uart = new char[1];
    char *uart2pc = new char[1];
    while (1) {
        if (pc.readable()) {
            pc.read(pc2uart, sizeof(pc2uart));
            uart.write(pc2uart, sizeof(pc2uart));
            pc_activity = !pc_activity;
        }
        if (uart.readable()) {
            uart.read(uart2pc, sizeof(uart2pc));
            pc.write(uart2pc, sizeof(uart2pc));
            uart_activity = !uart_activity;
        }
    }
}