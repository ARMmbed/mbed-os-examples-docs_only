/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

void flip(DigitalOut &led)
{
    led = !led;
}

int main()
{
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);

    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call_every(1s, flip, led1);
    queue.call_every(500ms, flip, led2);

    // events are executed by the dispatch method
    queue.dispatch_forever();
}
