/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include "mbed.h"
#include "mbed_mem_trace.h"


int main()
{
    mbed_mem_trace_set_callback(mbed_mem_trace_default_callback);
    while (true) {
        void *p = malloc(50);
        printf("50B allocated at %p\n", p);

        ThisThread::sleep_for(500);

        free(p);
        printf("50B freed at %p\n\n", p);
    }
}
