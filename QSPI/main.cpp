/*
* Copyright (c) 2018 ARM Limited. All rights reserved.
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

#if !DEVICE_QSPI
#error [NOT_SUPPORTED] QSPI not supported for this target
#endif

#include "mbed.h"
#include "drivers/QSPI.h"

#define CMD_WRITE          0x02
#define CMD_READ           0x03
#define CMD_ERASE          0x20
#define CMD_RDSR           0x5
#define CMD_WREN           0x6
#define CMD_RSTEN          0x66
#define CMD_RST            0x99
#define STATUS_REG_SIZE    2
#define BIT_WIP            0x1
#define BIT_WEL            0x2
#define BUF_SIZE           10

// hardware ssel (where applicable)
QSPI qspi_device(QSPI_FLASH1_IO0, QSPI_FLASH1_IO1, QSPI_FLASH1_IO2, QSPI_FLASH1_IO3, QSPI_FLASH1_SCK, QSPI_FLASH1_CSN); // io0, io1, io2, io3, sclk, ssel

static bool mem_ready()
{
    char status_value[STATUS_REG_SIZE] = {0xFF};
    int retries = 10000;
    bool mem_ready = true;

    do {
        retries--;
        if (QSPI_STATUS_OK != qspi_device.command_transfer(CMD_RDSR, -1, NULL, 0, status_value, STATUS_REG_SIZE)) {
            printf("Reading Status Register failed \n");
        }
        wait_ms(1);
    } while ((status_value[0] & BIT_WIP) != 0 && retries);

    if ((status_value[0] & BIT_WIP) != 0) {
        printf ("mem_ready FALSE: status value = 0x%x\n", (int)status_value[0]);
        mem_ready = false;
    }
    return mem_ready;
}

static int write_enable()
{
    char status_value[STATUS_REG_SIZE] = {0};
    int status = -1;

    if (QSPI_STATUS_OK != qspi_device.command_transfer(CMD_WREN, -1, NULL, 0, NULL, 0)) {
        printf("Sending WREN command FAILED \n");
        return status;
    }

    if (false == mem_ready()) {
        printf("Device not ready \n");
        return status;
    }

    if (QSPI_STATUS_OK != qspi_device.command_transfer(CMD_RDSR, -1, NULL, 0, status_value, STATUS_REG_SIZE)) {
        printf("Reading Status Register failed \n");
        return status;
    }

    if ((status_value[0] & BIT_WEL)) {
        status = 0;
    }
    return status;
}

static int flash_init()
{
    int status = QSPI_STATUS_OK;
    char status_value[STATUS_REG_SIZE] = {0};

    // Read the Status Register from device
    status =  qspi_device.command_transfer(CMD_RDSR, -1, NULL, 0, status_value, STATUS_REG_SIZE);
    if (status != QSPI_STATUS_OK) {
        printf("Reading Status Register failed: value = 0x%x\n", (int)status_value[0]);
        return status;
    }

    // Send Reset Enable
    status = qspi_device.command_transfer(CMD_RSTEN, -1, NULL, 0, NULL, 0);
    if (status == QSPI_STATUS_OK) {
        printf("Sending RSTEN Success \n");
    } else {
        printf("Sending RSTEN failed \n");
        return status;
    }

    if (false == mem_ready()) {
        printf("Device not ready \n");
        return -1;
    }

    // Send Reset
    status = qspi_device.command_transfer(CMD_RST, -1, NULL, 0, NULL, 0);
    if (status == QSPI_STATUS_OK) {
        printf("Sending RST Success \n");
    } else {
        printf("Sending RST failed \n");
        return status;
    }

    if (false == mem_ready()) {
        printf("Device not ready \n");
        return -1;
    }
    return status;
}

static int sector_erase(unsigned int flash_addr)
{
    if (0 != write_enable()) {
        printf("Write Enabe failed \n");
        return -1;
    }

    if (QSPI_STATUS_OK!= qspi_device.command_transfer(CMD_ERASE, (((int)flash_addr) & 0x00FFF000), NULL, 0, NULL, 0))
    {
        printf("Erase failed\n");
        return -1;
    }

    if (false == mem_ready()) {
        printf("Device not ready \n");
        return -1;
    }

    return 0;
}

int main() {
    char tx_buf[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    char rx_buf[BUF_SIZE] = {0};
    size_t buf_len = sizeof(tx_buf);
    qspi_status_t result;
    uint32_t address = 0x1000;

    result = qspi_device.configure_format(QSPI_CFG_BUS_SINGLE, QSPI_CFG_BUS_SINGLE,
                                        QSPI_CFG_ADDR_SIZE_24, QSPI_CFG_BUS_SINGLE,
                                        QSPI_CFG_ALT_SIZE_8, QSPI_CFG_BUS_SINGLE, 0);
    if (result != QSPI_STATUS_OK) {
        printf("Config format failed\n");
    }

    if (QSPI_STATUS_OK != flash_init()) {
        printf ("Init failed\n");
        return -1;
    }

    if (0 != sector_erase(address)) {
        return -1;
    }

    if (0 != write_enable()) {
        printf("Write Enabe failed \n");
        return -1;
    }

    result = qspi_device.write(CMD_WRITE, -1, address, tx_buf, &buf_len);
    if (result != QSPI_STATUS_OK) {
        printf("Write failed\n");
        return result;
    }
    printf("Write done: %s \n", tx_buf);

    if (false == mem_ready()) {
        printf("Device not ready \n");
        return -1;
    }

    result = qspi_device.read(CMD_READ, -1, address, rx_buf, &buf_len);
    if (result != QSPI_STATUS_OK) {
        printf("Read failed\n");
        return result;
    }

    printf ("Data Read = %s\n", rx_buf);
    return 0;
}
