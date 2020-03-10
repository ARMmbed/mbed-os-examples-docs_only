/*
 * Copyright (c) 2018-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int crc_sd_7bit()
{
    MbedCRC<POLY_7BIT_SD, 7> ct;
    char test[5];
    uint32_t crc;

    test[0] = 0x40;
    test[1] = 0x00;
    test[2] = 0x00;
    test[3] = 0x00;
    test[4] = 0x00;

    ct.compute((void *)test, 5, &crc);
    // CRC 7-bit as 8-bit data
    crc = (crc | 0x01) & 0xFF;
    printf("The CRC of 0x%lx \"CMD0\" is \"0x95\" Result: 0x%lx\n",
           ct.get_polynomial(), crc);

    test[0] = 0x48;
    test[1] = 0x00;
    test[2] = 0x00;
    test[3] = 0x01;
    test[4] = 0xAA;

    ct.compute((void *)test, 5, &crc);
    // CRC 7-bit as 8-bit data
    crc = (crc | 0x01) & 0xFF;
    printf("The CRC of 0x%lx \"CMD8\" is \"0x87\" Result: 0x%lx\n",
           ct.get_polynomial(), crc);

    test[0] = 0x51;
    test[1] = 0x00;
    test[2] = 0x00;
    test[3] = 0x00;
    test[4] = 0x00;

    ct.compute((void *)test, 5, &crc);
    // CRC 7-bit as 8-bit data
    crc = (crc | 0x01) & 0xFF;
    printf("The CRC of 0x%lx \"CMD17\" is \"0x55\" Result: 0x%lx\n",
           ct.get_polynomial(), crc);

    return 0;
}

int crc_sd_16bit()
{
    char test[512];
    uint32_t crc;
    MbedCRC<POLY_16BIT_CCITT, 16> sd(0, 0, false, false);

    memset(test, 0xFF, 512);
    // 512 bytes with 0xFF data --> CRC16 = 0x7FA1
    sd.compute((void *)test, 512, &crc);
    printf("16BIT SD CRC (512 bytes 0xFF) is \"0x7FA1\" Result: 0x%lx\n", crc);
    return 0;
}

int main()
{
    crc_sd_16bit();
    crc_sd_7bit();
    return 0;
}
