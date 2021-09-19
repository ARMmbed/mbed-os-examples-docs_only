/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

static UnbufferedSerial pc(USBTX, USBRX);
static UnbufferedSerial uart(D1, D0);
DigitalOut led1(LED1);
DigitalOut led4(LED_RED);
char *pc2uart = new char[1];
char *uart2pc = new char[1];

void uart_recv()
{
    led1 = !led1;
    while (uart.readable()) {
        uart.read(uart2pc, sizeof(uart2pc));
        pc.write(uart2pc, sizeof(uart2pc));
    }
}

void pc_recv()
{
    while (pc.readable()) {
        led4 = !led4;
        pc.read(pc2uart, sizeof(pc2uart));
        uart.write(pc2uart, sizeof(pc2uart));
    }
}

int main()
{
    pc.attach(&pc_recv, UnbufferedSerial::RxIrq);
    uart.attach(&uart_recv, UnbufferedSerial::RxIrq);

    while (1) {
        sleep();
    }
}
