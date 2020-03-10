/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "SDBlockDevice.h"
#include "MBRBlockDevice.h"
#include "FATFileSystem.h"

int main(void)
{
    // Create an SD card
    printf("Creating SD block device\n");
    SDBlockDevice sd(MBED_CONF_SD_SPI_MOSI, MBED_CONF_SD_SPI_MISO, MBED_CONF_SD_SPI_CLK, MBED_CONF_SD_SPI_CS);

    // Create a partition with 1 GB of space
    printf("Creating a partition with 1GB of space\n");
    MBRBlockDevice::partition(&sd, 1, 0x83, 0, 1024 * 1024);

    // Create the block device that represents the partition
    printf("Create the block device that represents the partition\n");
    MBRBlockDevice part1(&sd, 1);

    // Format the partition with a FAT filesystem
    printf("Format the partition with a FAT filesystem\n");
    FATFileSystem::format(&part1);

    // Create the FAT filesystem instance, files can now be written to
    // the FAT filesystem in partition 1
    printf("Create the FAT filesystem instance, files can now be written to the FAT filesystem in partition 1\n");
    FATFileSystem fat("fat", &part1);

    printf("To verify that the example worked, read the SD on a Windows machine.\n");
}
