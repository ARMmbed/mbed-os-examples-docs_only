/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "CellularNonIPSocket.h"
#include "CellularDevice.h"

// Network interface
NetworkInterface *iface;

int main()
{
    // Bring up the cellular interface
    iface = CellularContext::get_default_nonip_instance();
    MBED_ASSERT(iface);

    // sim pin, apn, credentials and possible plmn are taken automatically from json when using NetworkInterface::set_default_parameters()
    iface->set_default_parameters();

    printf("Cellular Non-IP Socket example\n");
    if (NSAPI_ERROR_OK != iface->connect() || NSAPI_STATUS_GLOBAL_UP != iface->get_connection_status()) {
        printf("Error connecting\n");
        return -1;
    }

    CellularNonIPSocket sock;

    nsapi_error_t retcode = sock.open((CellularContext *)iface);

    if (retcode != NSAPI_ERROR_OK) {
        printf("CellularNonIPSocket.open() fails, code: %d\n", retcode);
        return -1;
    }

    const char *send_string = "TEST";

    if (0 > sock.send((void *) send_string, sizeof(send_string))) {
        printf("Error sending data\n");
        return -1;
    }

    printf("Success sending data\n");

    char recv_buf[4];
    if (0 > sock.recv((void *)recv_buf, sizeof(recv_buf))) {
        printf("Error receiving data\n");
        return -1;
    }

    printf("Success receiving data\n");

    // Close the socket and bring down the network interface
    sock.close();
    iface->disconnect();
    return 0;
}
