/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono_literals;

int main()
{
    // Deep sleep for 1 second
    printf("Deep sleep allowed: %i\r\n", sleep_manager_can_deep_sleep());
    ThisThread::sleep_for(1s);

    // Lock deep sleep
    printf("Locking deep sleep\r\n");
    sleep_manager_lock_deep_sleep();

    // Sleep for 1 second
    printf("Deep sleep allowed: %i\r\n", sleep_manager_can_deep_sleep());
    ThisThread::sleep_for(1s);
}
