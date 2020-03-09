/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HeapBlockDevice.h"
#include "ChainingBlockDevice.h"
#include "FATFileSystem.h"

#define BLOCKSIZE 512

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

    // Format the new chained block device with a FAT filesystem
    FATFileSystem::format(&chainmem);

    // Create the FAT filesystem instance, files can now be written to
    // the FAT filesystem as if to a single 96 x 512 byte storage device
    FATFileSystem fat("fat", &chainmem);
}
