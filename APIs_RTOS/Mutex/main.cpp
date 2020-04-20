/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

Mutex stdio_mutex;
Thread t2;
Thread t3;

void notify(const char *name, int state)
{
    stdio_mutex.lock();
    printf("%s: %d\n\r", name, state);
    stdio_mutex.unlock();
}

void test_thread(const char *args)
{
    while (true) {
        notify(args, 0);
        ThisThread::sleep_for(1s);
        notify(args, 1);
        ThisThread::sleep_for(1s);
    }
}

int main()
{
    t2.start(callback(test_thread, "Th 2"));
    t3.start(callback(test_thread, "Th 3"));

    test_thread("Th 1");
}
