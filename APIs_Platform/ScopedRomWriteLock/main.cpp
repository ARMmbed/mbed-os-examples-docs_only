/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

int main()
{
    // Enable writing to ROM while in main
    ScopedRomWriteLock make_rom_writable;

    //custom_flash_programming();
}
