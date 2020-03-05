/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

int main()
{
    // 64-bit time doesn't wrap for half a billion years, at least
    uint64_t now = Kernel::get_ms_count();

    // wait a while
    ThisThread::sleep_for(10);

    uint64_t later = Kernel::get_ms_count();

    //calculate millisecs elapsed
    uint64_t elapsed_ms = later - now;

    printf("Elapsed ms: %u \r\n", (uint32_t)elapsed_ms);
}
