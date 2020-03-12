/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <mbed.h>

#if !DEVICE_I2CSLAVE
#error [NOT_SUPPORTED] I2C Slave is not supported
#endif

I2CSlave slave(D14, D15);

int main()
{
    char buf[10];
    char msg[] = "Slave!";

    slave.address(0xA0);
    while (1) {
        int i = slave.receive();
        switch (i) {
            case I2CSlave::ReadAddressed:
                slave.write(msg, strlen(msg) + 1); // Includes null char
                break;
            case I2CSlave::WriteGeneral:
                slave.read(buf, 10);
                printf("Read G: %s\n", buf);
                break;
            case I2CSlave::WriteAddressed:
                slave.read(buf, 10);
                printf("Read A: %s\n", buf);
                break;
        }
        for (int i = 0; i < 10; i++) {
            buf[i] = 0;    // Clear buffer
        }
    }
}
