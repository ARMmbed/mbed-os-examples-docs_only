/*
 * Copyright (c) 2018-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

Mutex mutex;
ConditionVariable cond(mutex);

// These variables are protected by locking mutex
uint32_t counter = 0;
bool done = false;

void worker_thread()
{
    mutex.lock();
    do {
        printf("Worker: Count %lu\r\n", counter);

        // Wait for a condition to change
        cond.wait();

    } while (!done);
    printf("Worker: Exiting\r\n");
    mutex.unlock();
}

int main()
{
    Thread thread;
    thread.start(worker_thread);

    for (int i = 0; i < 5; i++) {

        mutex.lock();
        // Change count and signal this
        counter++;
        printf("Main: Set count to %lu\r\n", counter);
        cond.notify_all();
        mutex.unlock();

        ThisThread::sleep_for(1000);
    }

    mutex.lock();
    // Change done and signal this
    done = true;
    printf("Main: Set done\r\n");
    cond.notify_all();
    mutex.unlock();

    thread.join();
}
