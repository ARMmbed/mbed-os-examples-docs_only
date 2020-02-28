/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

Thread thread;
DigitalOut led(LED1);

void led_thread()
{
    while (true) {
        // Signal flags that are reported as event are automatically cleared.
        ThisThread::flags_wait_any(0x1);
        led = !led;
    }
}

int main(void)
{
    thread.start(callback(led_thread));

    while (true) {
        ThisThread::sleep_for(1000);
        thread.flags_set(0x1);
    }
}
