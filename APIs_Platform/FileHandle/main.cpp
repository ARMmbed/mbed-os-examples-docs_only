/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

static DigitalOut led2(LED2);

// BufferedSerial derives from FileHandle
static BufferedSerial device(STDIO_UART_TX, STDIO_UART_RX);

int main()
{
    // Once set up, access through the C library
    FILE *devin = fdopen(&device, "r");

    while (1) {
        putchar(fgetc(devin));
        led2 = !led2;
    }
}
