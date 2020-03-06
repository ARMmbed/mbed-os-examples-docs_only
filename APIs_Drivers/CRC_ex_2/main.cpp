/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int main()
{
    MbedCRC<POLY_32BIT_ANSI, 32> ct;

    char  test[] = "123456789";
    uint32_t crc;

    ct.compute_partial_start(&crc);
    ct.compute_partial((void *)&test, 4, &crc);
    ct.compute_partial((void *)&test[4], 5, &crc);
    ct.compute_partial_stop(&crc);

    printf("The CRC of 0x%lx \"123456789\" is \"0xCBF43926\" Result: 0x%lx\n",
           ct.get_polynomial(), crc);

    return 0;
}
