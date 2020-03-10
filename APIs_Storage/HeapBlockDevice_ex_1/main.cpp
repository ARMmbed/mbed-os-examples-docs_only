/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HeapBlockDevice.h"

#define BLOCK_SIZE 512

HeapBlockDevice bd(2048, BLOCK_SIZE); // 2048 bytes with a block size of 512 bytes
uint8_t block[BLOCK_SIZE] = "Hello World!\n";

int main()
{
    bd.init();
    bd.erase(0, BLOCK_SIZE);
    bd.program(block, 0, BLOCK_SIZE);
    bd.read(block, 0, BLOCK_SIZE);
    printf("%s", block);
    bd.deinit();
}
