/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int main()
{
    MbedCRC<POLY_32BIT_ANSI, 32> ct;

    char  test[] = "123456789";
    uint32_t crc = 0;

    printf("\nPolynomial = 0x%lx  Width = %d \n", ct.get_polynomial(), ct.get_width());

    ct.compute((void *)test, strlen((const char *)test), &crc);
    printf("The CRC of data \"123456789\" is : 0x%lx\n", crc);
    return 0;
}
