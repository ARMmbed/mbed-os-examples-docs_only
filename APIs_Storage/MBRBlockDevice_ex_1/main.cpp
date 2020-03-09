/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HeapBlockDevice.h"
#include "MBRBlockDevice.h"

#define BLOCK_SIZE 512

int main(void)
{
    // Create a block device with 64 blocks of size 512
    printf("Create a block device with 64 blocks of size 512\n");
    HeapBlockDevice mem(64 * BLOCK_SIZE, BLOCK_SIZE);

    // Partition into two partitions with ~half the blocks
    printf("Partition into two partitions with ~half the blocks\n");
    MBRBlockDevice::partition(&mem, 1, 0x83, 0 * BLOCK_SIZE, 32 * BLOCK_SIZE);
    MBRBlockDevice::partition(&mem, 2, 0x83, 32 * BLOCK_SIZE);

    // Create a block device that maps to the first 32 blocks (excluding MBR block)
    printf("Create a block device that maps to the first 32 blocks (excluding MBR block)\n");
    MBRBlockDevice part1(&mem, 1);

    // Create a block device that maps to the last 32 blocks
    printf("Create a block device that maps to the last 32 blocks\n");
    MBRBlockDevice part2(&mem, 2);
}
