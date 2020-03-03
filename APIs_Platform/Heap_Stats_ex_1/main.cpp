/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_stats.h"

int main(void)
{
    mbed_stats_heap_t heap_stats;

    printf("Starting heap stats example\r\n");
    mbed_stats_heap_get(&heap_stats);
    printf("Start; Current heap: %lu\n", heap_stats.current_size);
    printf("Start; Max heap size: %lu\n", heap_stats.max_size);

    printf("\nAllocating 1000 bytes\n");
    void *allocation = malloc(1000);

    mbed_stats_heap_get(&heap_stats);
    printf("Post-Alloc; Current heap: %lu\n", heap_stats.current_size);
    printf("Post-Alloc; Max heap size: %lu\n", heap_stats.max_size);

    free(allocation);
    printf("\nFreed 1000 bytes\n");

    mbed_stats_heap_get(&heap_stats);
    printf("Post-Free; Current heap: %lu\n", heap_stats.current_size);
    printf("Post-Free; Max heap size: %lu\n", heap_stats.max_size);
}
