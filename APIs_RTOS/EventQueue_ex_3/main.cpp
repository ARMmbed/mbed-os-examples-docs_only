/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed_events.h"
#include <stdio.h>
using namespace std::chrono_literals;

/**
Event queues easily align with module boundaries, where internal state can be
implicitly synchronized through event dispatch. Multiple modules can use
independent event queues, but still be composed through the EventQueue::chain function.

Note the call() methods in this example only dispatch once as no period is
set and thus defaults to dispatch_once(). The ordering of the chaining dictates
the order of the dispatching.

Expected output:

hello from a!
hello from c!
hello from b!
**/

int main()
{
    // Create some event queues with pending events
    EventQueue a;
    a.call(printf, "hello from a!\n");

    EventQueue b;
    b.call(printf, "hello from b!\n");

    EventQueue c;
    c.call(printf, "hello from c!\n");

    // Chain c and b onto a's event queue. Both c and b will be dispatched
    // in the context of a's dispatch function.
    c.chain(&a);
    b.chain(&a);

    // Dispatching a will in turn dispatch b and c, printing hello from
    // all three queues
    a.dispatch_forever();
}
