/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HeapBlockDevice.h"
#include "ProfilingBlockDevice.h"

#define BLOCK_SIZE 512

HeapBlockDevice bd(2048, BLOCK_SIZE); // 2048 bytes with a block size of 512 bytes
uint8_t block[BLOCK_SIZE] = "Hello World!\n";

int main()
{
    ProfilingBlockDevice profiler(&bd);
    profiler.init();
    profiler.erase(0, BLOCK_SIZE);
    profiler.program(block, 0, BLOCK_SIZE);
    profiler.read(block, 0, BLOCK_SIZE);

    printf("%s", block);
    printf("read count: %lld\n", profiler.get_read_count());
    printf("program count: %lld\n", profiler.get_program_count());
    printf("erase count: %lld\n", profiler.get_erase_count());
}
