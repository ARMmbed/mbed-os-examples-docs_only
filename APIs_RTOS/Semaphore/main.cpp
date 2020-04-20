/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono_literals;

Semaphore one_slot(1);
Thread t2;
Thread t3;

void test_thread(const char *name)
{
    while (true) {
        one_slot.acquire();
        printf("%s\n\r", name);
        ThisThread::sleep_for(1s);
        one_slot.release();
    }
}

int main(void)
{
    t2.start(callback(test_thread, "Th 2"));
    t3.start(callback(test_thread, "Th 3"));

    test_thread("Th 1");
}
