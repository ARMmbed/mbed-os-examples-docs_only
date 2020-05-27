/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"

int main()
{
    printf("TCP server example\n");

    EthernetInterface eth;
    eth.connect();

    SocketAddress a;
    eth.get_ip_address(&a);
    a.set_port(23);

    printf("The Server IP address is '%s'\n", a.get_ip_address());

    TCPSocket srv;
    TCPSocket *client_sock;
    SocketAddress client_addr;
    char *buffer = new char[256];

    /* Open the server on ethernet stack */
    srv.open(&eth);

    /* Accepts a connection on a socket. */
    srv.bind(a);

    /* Can handle x simultaneous connections */
    srv.listen(1);

    nsapi_error_t error;
    client_sock = srv.accept(&error);

    client_sock->getpeername(&a);

    printf("Accepted %s:%d\n", a.get_ip_address(),
           a.get_port());
    strcpy(buffer, "Hello \n\r");
    client_sock->send(buffer, strlen(buffer));
    client_sock->recv(buffer, 256);

    client_sock->close();
    srv.close();
    delete[] buffer;
}
