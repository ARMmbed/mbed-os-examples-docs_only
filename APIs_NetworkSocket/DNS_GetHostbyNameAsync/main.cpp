/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "nsapi_types.h"
#include "EthernetInterface.h"
#include "SocketAddress.h"
#include "Semaphore.h"

rtos::Semaphore callback_semaphore;
SocketAddress address;
nsapi_error_t result;

// Callback for asynchronous host name resolution
void hostbyname_callback(nsapi_error_t res, SocketAddress *addr)
{
    // Store result and release semaphore
    result = res;
    address = *addr;
    callback_semaphore.release();
}

int main()
{
    // Initialise network interface
    EthernetInterface eth;
    eth.connect();

    // Initiate asynchronous DNS host name resolution
    eth.gethostbyname_async("www.mbed.com", hostbyname_callback);

    // Wait for callback semaphore
    callback_semaphore.acquire();

    // Print result
    printf("Result %s, Address %s\r\n", result == NSAPI_STATUS_GLOBAL_UP ? "OK" : "FAIL",
           result == NSAPI_STATUS_GLOBAL_UP ? address.get_ip_address() : "NONE");

    // Disconnect network interface
    eth.disconnect();
}
