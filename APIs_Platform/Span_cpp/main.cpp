/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "platform/Span.h"

template<typename T>
Span<const T> split(Span<const T> &range, const T &separator)
{
    const ptrdiff_t out_of_range = range.size();

    ptrdiff_t start;
    for (start = 0; start != out_of_range && range[start] == separator; ++start) { }

    ptrdiff_t last;
    for (last = start; last != out_of_range && range[last] != separator; ++last) { }

    Span<const T> result = range.subspan(start, last - start);
    range = range.subspan(last);
    return result;
}


int main()
{
    Span<const char> buffer("Hello World! Hello mbed-os!");
    while (buffer.empty() == false) {
        Span<const char> token = split(buffer, ' ');
        printf("token: %.*s\r\n", token.size(), token.data());
    }
}
