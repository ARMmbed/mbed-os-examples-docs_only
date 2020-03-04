/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

int main()
{
    // Enable execution from RAM while in main
    ScopedRamExecutionLock make_ram_executable;

    //some_function_in_ram();
}
