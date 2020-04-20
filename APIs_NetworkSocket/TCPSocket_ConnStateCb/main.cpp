/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "EthernetInterface.h"
#include "mbed.h"
#include "nsapi_types.h"

using namespace std::chrono_literals;

// Network interface
EthernetInterface eth;
Mutex print_mutex;

void safe_print(const char *msg)
{
    print_mutex.lock();
    printf(msg);
    print_mutex.unlock();
}

void status_callback(nsapi_event_t status, intptr_t param)
{
    safe_print("Connection status changed!\r\n");
    switch (param) {
        case NSAPI_STATUS_LOCAL_UP:
            safe_print("Local IP address set!\r\n");
            break;
        case NSAPI_STATUS_GLOBAL_UP:
            safe_print("Global IP address set!\r\n");
            break;
        case NSAPI_STATUS_DISCONNECTED:
            safe_print("No connection to network!\r\n");
            break;
        case NSAPI_STATUS_CONNECTING:
            safe_print("Connecting to network!\r\n");
            break;
        default:
            safe_print("Not supported\r\n");
            break;
    }
}

int main()
{
    safe_print("Status callback example!\r\n");

    eth.attach(&status_callback);
    eth.set_blocking(false);

    safe_print("Connecting...\r\n");
    eth.connect();

    safe_print("Connecting started...\r\n");
    ThisThread::sleep_for(10s);

    safe_print("Disconnect\r\n");
    eth.disconnect();

    safe_print("Done\r\n");
}
