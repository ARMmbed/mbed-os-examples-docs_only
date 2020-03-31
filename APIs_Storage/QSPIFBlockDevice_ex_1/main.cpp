/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#if !DEVICE_QSPI
#error [NOT_SUPPORTED] QSPI not supported for this target
#endif

#include "mbed.h"
#include <stdio.h>
#include <algorithm>
#include "QSPIFBlockDevice.h"

QSPIFBlockDevice bd(QSPI_FLASH1_IO0, QSPI_FLASH1_IO1, QSPI_FLASH1_IO2, QSPI_FLASH1_IO3,
                    QSPI_FLASH1_SCK, QSPI_FLASH1_CSN, QSPIF_POLARITY_MODE_0, MBED_CONF_QSPIF_QSPI_FREQ);

// Entry point for the example
int main()
{
    printf("--- Mbed OS QSPIF block device example ---\n");

    // Initialize the block device
    int err = bd.init();
    printf("bd.init -> %d\n", err);

    int erase_val = bd.get_erase_value();

    // Get device geometry
    bd_size_t read_size    = bd.get_read_size();
    bd_size_t program_size = bd.get_program_size();
    bd_size_t erase_size   = bd.get_erase_size();
    bd_size_t size         = bd.size();

    printf("--- Block device geometry ---\n");
    printf("read_size:    %lld B\n", read_size);
    printf("program_size: %lld B\n", program_size);
    printf("erase_size:   %lld B\n", erase_size);
    printf("size:         %lld B\n", size);
    printf("---\n");

    // Allocate a block with enough space for our data, aligned to the
    // nearest program_size. This is the minimum size necessary to write
    // data to a block.
    size_t buffer_size = sizeof("Hello Storage!") + program_size - 1;
    buffer_size = buffer_size - (buffer_size % program_size);
    char *buffer = new char[buffer_size];

    // Read what is currently stored on the block device. We haven't written
    // yet so this may be garbage
    printf("bd.read(%p, %d, %d)\n", buffer, 0, buffer_size);
    err = bd.read(buffer, 0, buffer_size);
    printf("bd.read -> %d\n", err);

    printf("--- Stored data ---\n");
    for (size_t i = 0; i < buffer_size; i += 16) {
        for (size_t j = 0; j < 16; j++) {
            if (i + j < buffer_size) {
                printf("%02x ", buffer[i + j]);
            } else {
                printf("   ");
            }
        }

        printf(" %.*s\n", buffer_size - i, &buffer[i]);
    }
    printf("---\n");

    // Update buffer with our string we want to store
    strncpy(buffer, "Hello Storage!", buffer_size);

    // Write data to first block, write occurs in two parts,
    // an erase followed by a program
    printf("bd.erase(%d, %lld)\n", 0, erase_size);
    err = bd.erase(0, erase_size);
    printf("bd.erase -> %d\n", err);

    printf("bd.program(%p, %d, %d)\n", buffer, 0, buffer_size);
    err = bd.program(buffer, 0, buffer_size);
    printf("bd.program -> %d\n", err);

    // Clobber the buffer so we don't get old data
    memset(buffer, 0xcc, buffer_size);

    // Read the data from the first block, note that the program_size must be
    // a multiple of the read_size, so we don't have to check for alignment
    printf("bd.read(%p, %d, %d)\n", buffer, 0, buffer_size);
    err = bd.read(buffer, 0, buffer_size);
    printf("bd.read -> %d\n", err);

    printf("--- Stored data ---\n");
    for (size_t i = 0; i < buffer_size; i += 16) {
        for (size_t j = 0; j < 16; j++) {
            if (i + j < buffer_size) {
                printf("%02x ", buffer[i + j]);
            } else {
                printf("   ");
            }
        }

        printf(" %.*s\n", buffer_size - i, &buffer[i]);
    }
    printf("---\n");

    // Deinitialize the block device
    printf("bd.deinit()\n");
    err = bd.deinit();
    printf("bd.deinit -> %d\n", err);

    printf("--- done! ---\n");
}
