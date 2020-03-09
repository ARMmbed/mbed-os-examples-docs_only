/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HeapBlockDevice.h"
#include "ChainingBlockDevice.h"

#define BLOCKSIZE 512
char buffer1[BLOCKSIZE];
char buffer2[BLOCKSIZE];

int main(void)
{
    // Create two smaller block devices with
    // 64 and 32 blocks of size 512 bytes
    HeapBlockDevice mem1(64 * BLOCKSIZE, BLOCKSIZE);
    HeapBlockDevice mem2(32 * BLOCKSIZE, BLOCKSIZE);

    // Create a block device backed by mem1 and mem2
    // contains 96 blocks of size 512 bytes
    BlockDevice *bds[] = {&mem1, &mem2};
    ChainingBlockDevice chainmem(bds);

    // Initialize the block devices
    chainmem.init();

    // Erase the block device to prepare for programming. 64 and 32 refer to
    // the respective number of blocks in mem1 and mem2
    chainmem.erase(0, (BLOCKSIZE * (64 + 32)));

    // Program strings to the block device at byte-addressable locations that
    // span both sub blocks. The second program will write past the end of the
    // first block
    chainmem.program("data for block", 0, BLOCKSIZE);
    chainmem.program("Some more data", (65 * BLOCKSIZE), BLOCKSIZE);

    // Readback the written values
    chainmem.read(&buffer1, 0, BLOCKSIZE);
    chainmem.read(&buffer2, (65 * BLOCKSIZE), BLOCKSIZE);
    printf("Read back: %s, %s\r\n", buffer1, buffer2);
}
