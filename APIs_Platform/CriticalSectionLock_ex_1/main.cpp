/*
 * Copyright (c) 2017 - 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define  USE_CRITICAL_SECTION_LOCK      1   // Set 0 to see race condition
// Note: Might require few runs to see race condition

#define THREAD_CNT  8

int32_t value = 100000;
volatile int32_t counter = 0;

void increment(void)
{
    for (int i = 0; i < value; i++) {
#if (USE_CRITICAL_SECTION_LOCK == 1)
        CriticalSectionLock  lock;
#endif
        counter += 1;
    }
}

int get_count(void)
{
    if (counter == (value * THREAD_CNT)) {
        printf("No Race condition\n");
    } else {
        printf("Race condition\n");
    }
    return counter;
}

int main()
{
    Thread counter_thread[THREAD_CNT];

    for (int i = 0; i < THREAD_CNT; i++) {
        counter_thread[i].start(callback(increment));
    }

    // Wait for the threads to finish
    for (int i = 0; i < THREAD_CNT; i++) {
        counter_thread[i].join();
    }
    printf("Counter = %d\n", get_count());
}
