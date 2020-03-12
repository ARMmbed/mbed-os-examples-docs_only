/*
 * Copyright (c) 2017 - 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/CircularBuffer.h"

#define BUF_SIZE    10

CircularBuffer<char, BUF_SIZE> buf;
char data_stream[] = "DataToBeAddedToBuffer";

int main()
{
    uint32_t bytes_written = 0;

    while (!buf.full()) {
        buf.push(data_stream[bytes_written++]);
    }

    printf("Circular buffer is full: \"%s\" or empty: \"%s\" \n",
           (buf.full() ? "true" : "false"),
           (buf.empty() ? "true" : "false"));
    printf("Bytes written %ld \n", bytes_written);

    // If buffer is full, contents will be over-written
    buf.push(data_stream[bytes_written++]);

    char data = 0;
    printf("Buffer contents: ");
    while (!buf.empty()) {
        buf.pop(data);
        printf("%c", data);
    }
    printf("\n");

    printf("Circular buffer is full: \"%s\" or empty: \"%s\" \n",
           (buf.full() ? "true" : "false"),
           (buf.empty() ? "true" : "false"));

    return 0;

}
