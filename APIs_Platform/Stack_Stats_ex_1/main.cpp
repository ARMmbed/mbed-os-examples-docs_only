/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_stats.h"

int main(void)
{
    printf("Starting stack stats example\r\n");

    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stats = (mbed_stats_stack_t *) malloc(cnt * sizeof(mbed_stats_stack_t));

    if (stats) {
        cnt = mbed_stats_stack_get_each(stats, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("Thread: 0x%lx, Stack size: %u, Max stack: %u\r\n",
                   stats[i].thread_id, stats[i].reserved_size, stats[i].max_size);
        }
        free(stats);
    }
}
