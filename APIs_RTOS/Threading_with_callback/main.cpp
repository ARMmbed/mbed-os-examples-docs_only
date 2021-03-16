/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono_literals;

Thread thread;
DigitalOut led1(LED1);
volatile bool running = true;

// Blink function toggles the led in a long running loop
void blink(DigitalOut *led)
{
    while (running) {
        *led = !*led;
        ThisThread::sleep_for(1s);
    }
}

// Spawns a thread to run blink for 5 seconds
int main()
{
    thread.start(callback(blink, &led1));
    ThisThread::sleep_for(5s);
    running = false;
    thread.join();
}
