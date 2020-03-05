/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
// Here's an example using the AT45DB on the K64F
#include "mbed.h"
#include "DataFlashBlockDevice.h"

// Create DataFlash on SPI bus with PTE5 as chip select
DataFlashBlockDevice dataflash(PTE1, PTE3, PTE2, PTE4);

// Create DataFlash on SPI bus with PTE6 as write-protect
// DataFlashBlockDevice dataflash(PTE1, PTE3, PTE2, PTE4, PTE6);

int main()
{
    printf("dataflash test\n");

    // Initialize the SPI flash device and print the memory layout
    dataflash.init();
    printf("dataflash size: %llu\n", dataflash.size());
    printf("dataflash read size: %llu\n", dataflash.get_read_size());
    printf("dataflash program size: %llu\n", dataflash.get_program_size());
    printf("dataflash erase size: %llu\n", dataflash.get_erase_size());

    // Write "Hello World!" to the first block
    char *buffer = (char *)malloc(dataflash.get_erase_size());
    sprintf(buffer, "Hello World!\n");
    dataflash.erase(0, dataflash.get_erase_size());
    dataflash.program(buffer, 0, dataflash.get_erase_size());

    // Read back what was stored
    dataflash.read(buffer, 0, dataflash.get_erase_size());
    printf("%s", buffer);

    // Deinitialize the device
    dataflash.deinit();
}
