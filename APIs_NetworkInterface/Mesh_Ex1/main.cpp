/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int main(void)
{
    MeshInterface *mesh = MeshInterface::get_default_instance();

    int status = mesh->connect();
    if (status) {
        printf("Connection failed! error %d\n", status);
        return status;
    }

    printf("Connected!\n");

    UDPSocket sock;
    status = sock.open(mesh);
    if (status) {
        printf("Failed to open socket, error %d\n", status);
    }

    // Now the interface is connected, and I can communicate with Sockets
}
