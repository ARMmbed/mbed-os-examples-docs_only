/*
* Copyright (c) 2019 ARM Limited. All rights reserved.
* SPDX-License-Identifier: Apache-2.0
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "mbed.h"
#include "USBCDC_ECM.h"

/* Ethernet II frame */
typedef struct {
    uint8_t dst_mac[6];
    uint8_t src_mac[6];
    uint16_t eth_type;
    char payload[12];
} packet_t;

static packet_t packet = {
    .dst_mac = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    .src_mac = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc},
    .eth_type = 0xaaaa, /* unused EtherType */
    .payload = "Hello world"
};

USBCDC_ECM ecm;

int main()
{
    while (true) {
        ecm.send((uint8_t *)&packet, sizeof(packet));
        wait(1.0);
    }
}
