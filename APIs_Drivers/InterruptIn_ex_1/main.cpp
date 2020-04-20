/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

using namespace std::chrono_literals;

class Counter {
public:
    Counter(PinName pin) : _interrupt(pin)          // create the InterruptIn on the pin specified to Counter
    {
        _interrupt.rise(callback(this, &Counter::increment)); // attach increment function of this counter instance
    }

    void increment()
    {
        _count++;
    }

    int read()
    {
        return _count;
    }

private:
    InterruptIn _interrupt;
    volatile int _count;
};

Counter counter(SW2);

int main()
{
    while (1) {
        printf("Count so far: %d\n", counter.read());
        ThisThread::sleep_for(2s);
    }
}
