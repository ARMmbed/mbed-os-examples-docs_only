/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// A class for flip()-ing a DigitalOut
class Flipper {
public:
    Flipper(PinName pin) : _pin(pin)
    {
        _pin = 0;
    }
    void flip()
    {
        _pin = !_pin;
    }
private:
    DigitalOut _pin;
};

DigitalOut led1(LED1);
Flipper f(LED2);
Timeout t;

int main()
{
    // the address of the object, member function, and interval
    t.attach(callback(&f, &Flipper::flip), 2.0);

    // spin in a main loop. flipper will interrupt it to call flip
    while (1) {
        led1 = !led1;
        ThisThread::sleep_for(200);
    }
}
