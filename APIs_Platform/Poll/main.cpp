/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// Pins for each port are specified using mbed_app.json. Assume no flow control.
// (If there were flow control, being blocked by it could break the implementation,
// as you would stop reading input in the opposite direction).
BufferedSerial device1(MBED_CONF_APP_UART1_TX, MBED_CONF_APP_UART1_RX);
BufferedSerial device2(MBED_CONF_APP_UART2_TX, MBED_CONF_APP_UART2_RX);

// Precondition: "in" is readable
static void copy_some(FileHandle *out, FileHandle *in)
{
    // To ensure performance, try to read multiple bytes at once,
    // but don't expect to read many in practice.
    char buffer[32];



    // Despite the FileHandle being in its default blocking mode,
    // read() must return immediately with between 1-32 bytes, as
    // you've already checked that `in` is ready with poll()
    ssize_t read = in->read(buffer, sizeof buffer);
    if (read <= 0) {
        error("Input error");
    }

    // Write everything out. Assuming output port is same speed as input,
    // and no flow control, this may block briefly but not significantly.
    ssize_t written = out->write(buffer, read);
    if (written < read) {
        error("Output error");
    }
}

// Transfer bidirectional data between two ports, acting as a virtual link.
// poll() is used to monitor both ports for input.
int main()
{
    pollfh fds[2];

    fds[0].fh = &device1;
    fds[0].events = POLLIN;
    fds[1].fh = &device2;
    fds[1].events = POLLIN;

    while (1) {
        // Block indefinitely until either of the 2 ports is readable (or has an error)
        poll(fds, 2, -1);

        // Transfer some data in either or both directions
        if (fds[0].revents) {
            copy_some(fds[1].fh, fds[0].fh);
        }
        if (fds[1].revents) {
            copy_some(fds[0].fh, fds[1].fh);
        }
    }
}
