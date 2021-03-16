/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono;

int main()
{
    // 64-bit time doesn't wrap for half a billion years, at least
    Kernel::Clock::time_point now = Kernel::Clock::now();

    // wait a while
    ThisThread::sleep_for(10ms);

    Kernel::Clock::time_point later = Kernel::Clock::now();

    //calculate millisecs elapsed
    milliseconds elapsed_ms = later - now;

    printf("Elapsed ms: %u \r\n", (uint32_t)elapsed_ms.count());
}
