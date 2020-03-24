/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

static BufferedSerial pc(USBTX, USBRX); // tx, rx
PwmOut led(LED1);

float brightness = 0.0;

int main()
{
    char msg[] = "Press 'u' to turn LED1 brightness up, 'd' to turn it down\n";
    char *c = new char[1];
    pc.write(msg, sizeof(msg));

    while (1) {
        pc.read(c, sizeof(c));
        pc.write(c, sizeof(c));
        if ((*c == 'u') && (brightness < 0.5)) {
            brightness += 0.01;
            led = brightness;
        }
        if ((*c == 'd') && (brightness > 0.0)) {
            brightness -= 0.01;
            led = brightness;
        }
    }

}