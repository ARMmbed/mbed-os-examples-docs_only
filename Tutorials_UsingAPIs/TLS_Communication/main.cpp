/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_trace.h"

const char cert[] = /* your certificate, see above */ "";

int main(void)
{

    nsapi_size_or_error_t result;
    NetworkInterface *net = NetworkInterface::get_default_instance();

    if (!net) {
        printf("Error! No network inteface found.\n");
        return 0;
    }

    printf("Connecting to network\n");
    result = net->connect();
    if (result != 0) {
        printf("Error! net->connect() returned: %d\n", result);
        return result;
    }

    TLSSocket *socket = new TLSSocket;
    result = socket->set_root_ca_cert(cert);
    if (result != 0) {
        printf("Error: socket->set_root_ca_cert() returned %d\n", result);
        return result;
    }

    result = socket->open(net);
    if (result != 0) {
        printf("Error! socket->open() returned: %d\n", result);
        return result;
    }

    printf("Connecting to os.mbed.com\n");
    result = socket->connect(SocketAddress("os.mbed.com", 443));
    if (result != 0) {
        printf("Error! socket->connect() returned: %d\n", result);
        return result;
    }
}
