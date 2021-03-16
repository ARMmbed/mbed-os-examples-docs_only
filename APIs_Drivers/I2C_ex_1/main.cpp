/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

// Read temperature from LM75BD

I2C i2c(I2C_SDA, I2C_SCL);

const int addr7bit = 0x48;      // 7 bit I2C address
const int addr8bit = 0x48 << 1; // 8bit I2C address, 0x90

int main()
{
    char cmd[2];
    while (1) {
        cmd[0] = 0x01;
        cmd[1] = 0x00;
        i2c.write(addr8bit, cmd, 2);

        ThisThread::sleep_for(500ms);

        cmd[0] = 0x00;
        i2c.write(addr8bit, cmd, 1);
        i2c.read(addr8bit, cmd, 2);

        float tmp = (float((cmd[0] << 8) | cmd[1]) / 256.0);
        printf("Temp = %.2f\n", tmp);
    }
}
