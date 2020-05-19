/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_events.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);

int main()
{
    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call_every(1000, [] {
        led1 = !led1;
    });
    queue.call_every(500, [] {
        led2 = !led2;
    });

    // events are executed by the dispatch method
    queue.dispatch_forever();
}
