/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed_events.h"
#include <stdio.h>
using namespace std::chrono_literals;

// In the example below there are 3 types of event callbacks
// 1) Call the provided function immediately
// 2) Call the provided function once (after the specified period)
// 3) Call the provided function every specified period
//
// Expected output:
//
// called immediately
// called every 1 seconds
// called in 2 seconds
// called every 1 seconds
// called every 1 seconds
//    ^ repeated forever
//
int main()
{
    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call(printf, "called immediately\n");
    queue.call_in(2000ms, printf, "called in 2 seconds\n");
    queue.call_every(1000ms, printf, "called every 1 seconds\n");

    // events are executed by the dispatch_forever method
    queue.dispatch_forever();
}
