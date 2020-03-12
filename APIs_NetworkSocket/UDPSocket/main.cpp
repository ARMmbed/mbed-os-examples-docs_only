/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "EthernetInterface.h"
#include "LWIPStack.h"

// Network interface
EthernetInterface net;

// Time protocol implementation : Address: time.nist.gov UDPPort: 37

typedef struct {
    uint32_t secs;         // Transmit Time-stamp seconds.
} ntp_packet;

int main()
{
    SocketAddress sockAddr;

    // Bring up the ethernet interface
    printf("UDP Socket example\n");
    if (0 != net.connect()) {
        printf("Error connecting\n");
        return -1;
    }

    // Show the network address
    net.get_ip_address(&sockAddr);
    printf("IP address is: %s\n", sockAddr.get_ip_address() ? sockAddr.get_ip_address() : "No IP");

    UDPSocket sock;
    sock.open(&net);

    net.gethostbyname("time.nist.gov", &sockAddr);
    sockAddr.set_port(37);

    char out_buffer[] = "time";
    if (0 > sock.sendto(sockAddr, out_buffer, sizeof(out_buffer))) {
        printf("Error sending data\n");
        return -1;
    }

    ntp_packet in_data;
    sock.recvfrom(&sockAddr, &in_data, sizeof(ntp_packet));
    in_data.secs = ntohl(in_data.secs) - 2208988800;      // 1900-1970
    printf("Time Received %lu seconds since 1/01/1900 00:00 GMT\n",
           (uint32_t)in_data.secs);
    printf("Time = %s", ctime((const time_t *)&in_data.secs));

    printf("Time Server Address: %s Port: %d\n\r",
           sockAddr.get_ip_address(), sockAddr.get_port());

    // Close the socket and bring down the network interface
    sock.close();
    net.disconnect();
    return 0;
}
