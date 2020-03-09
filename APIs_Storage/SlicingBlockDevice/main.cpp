/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HeapBlockDevice.h"
#include "SlicingBlockDevice.h"

#define BLOCK 512
#define NUMSLICES 3

char buff[BLOCK];

int main(void)
{
    // Create a block device with 64 blocks of size 512
    HeapBlockDevice mem(64 * BLOCK, BLOCK);

    SlicingBlockDevice slices[NUMSLICES] = {
        // Create a block device that maps to the first 32 blocks
        SlicingBlockDevice(&mem, 0 * BLOCK, 32 * BLOCK),

        // Create a block device that maps to the middle 32 blocks
        SlicingBlockDevice(&mem, 16 * BLOCK, -16 * BLOCK),

        // Create a block device that maps to the last 32 blocks
        SlicingBlockDevice(&mem, 32 * BLOCK)
    };

    for (int i = 0; i < NUMSLICES; i++) {
        // Initialize and erase the slice to prepar for programming
        slices[i].init();
        slices[i].erase(0, 32 * BLOCK);

        // Construct the message for the block and write to the slice
        sprintf((char *)&buff, "test: %d", i);
        slices[i].program(&buff, 0, BLOCK);
    }

    for (int i = 0; i < NUMSLICES; i++) {
        // Read back the programmed blocks through the underlying block device
        mem.read(&buff, (i * 16 * BLOCK), BLOCK);
        printf("%s  --> ", buff);

        // Read back the programmed blocks through the sliced block device.
        slices[i].read(&buff, 0, BLOCK);
        printf("%s\r\n", buff);
    }
}
