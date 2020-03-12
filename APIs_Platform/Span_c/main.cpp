/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "platform/Span.h"

template<typename T>
void split(const T **in_ptr, ptrdiff_t *in_size, const T **token_ptr, ptrdiff_t *token_size, const T &separator)
{
    const ptrdiff_t out_of_range = *in_size;

    ptrdiff_t start;
    for (start = 0; start != out_of_range && (*in_ptr)[start] == separator; ++start) { }

    ptrdiff_t last;
    for (last = start; last != out_of_range && (*in_ptr)[last] != separator; ++last) { }

    *token_ptr = *in_ptr + start;
    *token_size = last - start;

    *in_size = *in_size - last;
    *in_ptr = *in_ptr + last;
}

int main()
{
    const char str[] = "Hello World! Hello mbed-os!";
    const char *buffer_ptr = str;
    ptrdiff_t buffer_size = sizeof(str);
    while (buffer_size) {
        const char *token_ptr = NULL;
        ptrdiff_t token_size = 0;
        split(&buffer_ptr, &buffer_size, &token_ptr, &token_size, ' ');
        printf("token: %.*s\r\n", token_size, token_ptr);
    }
}
