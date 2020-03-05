/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

BusIn nibble(D0, D1, D2, D3); // Change these pins to buttons on your board.

int main()
{

    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
    nibble.mode(PullNone);

    while (1) {
        // check bits set in nibble
        switch (nibble & nibble.mask()) { // read the bus and mask out bits not being used
            case 0x0:
                printf("0b0000, D3,D2,D1,D0 are low  \n\r");
                break;
            case 0x1:
                printf("0b0001,          D0  is high \n\r");
                break;
            case 0x2:
                printf("0b0010,       D1     is high \n\r");
                break;
            case 0x3:
                printf("0b0011,       D1,D0 are high \n\r");
                break;
            case 0x4:
                printf("0b0100,    D2        is high \n\r");
                break;
            case 0x5:
                printf("0b0101,    D2,  ,D0 are high \n\r");
                break;
            case 0x6:
                printf("0b0110,    D2,D1    are high \n\r");
                break;
            case 0x7:
                printf("0b0111,    D2,D1,D0 are high \n\r");
                break;
            case 0x8:
                printf("0b1000, D3           is high \n\r");
                break;
            // ...
            case 0xF:
                printf("0b1111, D3,D2,D1,D0 are high \n\r");
                break;
        }
        ThisThread::sleep_for(1000);
    }
}
