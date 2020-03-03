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

#include "mbed.h"
#include "DeviceKey.h"

// Print a unsigned char buffer in hex format
void print_buffer(unsigned char *buf, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("%02X", buf[i]);
    }
}

// Injection of a dummy key when there is no TRNG
int inject_rot_key()
{
    uint32_t key[DEVICE_KEY_16BYTE / sizeof(uint32_t)];

    memset(key, 0, DEVICE_KEY_16BYTE);
    memcpy(key, "ABCDEF1234567890", DEVICE_KEY_16BYTE);
    int size = DEVICE_KEY_16BYTE;
    DeviceKey &devkey = DeviceKey::get_instance();
    return devkey.device_inject_root_of_trust(key, size);
}

// Entry point for the example
int main()
{
    unsigned char derive_key1 [DEVICE_KEY_32BYTE];
    unsigned char salt1[] = "SALT1 ----- SALT1 ------ SALT1";
    int ret = DEVICEKEY_SUCCESS;

    printf("\nMbed OS DeviceKey example \n");

    // DeviceKey is a singleton
    DeviceKey &devkey = DeviceKey::get_instance();

#if !defined(DEVICE_TRNG)

    // If TRNG is not available it is a must to inject the ROT before the first call to derive key method.
    printf("No TRNG support for this device. injecting ROT.\n");
    ret = inject_rot_key();
    if (DEVICEKEY_SUCCESS != ret && DEVICEKEY_ALREADY_EXIST != ret) {
        printf("Error, injection of ROT key has failed with status %d\n", ret);
        return -1;
    }

    if (DEVICEKEY_ALREADY_EXIST == ret) {
        printf("ROT Key already exists in the persistent memory.\n", ret);
    } else {
        printf("ROT Key injected and stored in persistent memory.\n", ret);
    }

#endif

    printf("Salt for key derivation: %s \n", salt1);

    // 16 byte key derivation.
    ret = devkey.generate_derived_key(salt1, sizeof(salt1), derive_key1, DEVICE_KEY_16BYTE);
    if (DEVICEKEY_SUCCESS != ret) {
        printf("Error, derive key failed with error code %d \n", ret);
        return -1;
    }

    printf("16-byte Derived key is: ");
    print_buffer(derive_key1, DEVICE_KEY_16BYTE);
    printf("\n");

    printf("Mbed OS DeviceKey example done.\n");

    return 0;
}