/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

DigitalOut led1(LED1);
InterruptIn sw(SW2);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;


void rise_handler(void)
{
    queue.call(printf, "rise_handler in context %p\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

void fall_handler(void)
{
    printf("rise_handler in context %p\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

int main()
{
    // Start the event queue
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    printf("Starting in context %p\r\n", ThisThread::get_id());
    // The 'rise' handler will execute in IRQ context
    sw.rise(rise_handler);
    // The 'fall' handler will execute in the context of thread 't'
    sw.fall(queue.event(fall_handler));
}
