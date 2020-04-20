/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono_literals;

Ticker ticker;
Thread thread;
Queue<const char *, 5> trail;

// Since we're printing from multiple threads, we need a mutex
Mutex print_lock;

enum ExecutionTypes {
    IDLE,
    USER,
    ISR
};

const char *ExecutionMessages[] = {
    "the idle thread",
    "a user thread",
    "interrupt context"
};

void handler()
{
    // Check to see if we're in interrupt context
    if (core_util_is_isr_active()) {
        // Do not print since we're in interrupt context
        trail.put(&(ExecutionMessages[ISR]));
    } else {
        // Safe to print since we're in a user thread
        print_lock.lock();
        printf("Starting user thread\r\n");
        print_lock.unlock();
        while (true) {
            trail.put(&(ExecutionMessages[USER]));
            ThisThread::sleep_for(500ms);
        }
    }
}

void custom_idle_function()
{
    // Custom idle behavior would go here
    // We won't print here since the default idle thread's stack is too small
    trail.put(&(ExecutionMessages[IDLE]));

    // Switch back to the default idle behavior
    Kernel::attach_idle_hook(NULL);
}

int main()
{
    printf("Starting execution example\r\n");

    // Attach the custom idle thread function
    Kernel::attach_idle_hook(custom_idle_function);

    // Trigger the interrupt every 3 seconds
    ticker.attach(handler, 3);

    // Start the user thread
    thread.start(handler);

    // Get the past exectuion trail
    while (true) {
        osEvent evt = trail.get();
        if (evt.status != osEventMessage) {
            print_lock.lock();
            printf("Failed to retrieve the execution trail (returned %02lx)\r\n", evt.status);
            print_lock.unlock();
        } else {
            print_lock.lock();
            printf("Execution was in %s\r\n", *(const char **)evt.value.v);
            print_lock.unlock();
        }
    }
}
