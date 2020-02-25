/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "mbed_events.h"

DigitalOut led1(LED1);
InterruptIn sw(SW2);

void rise_handler(void)
{
    // Toggle LED
    led1 = !led1;
}

void fall_handler(void)
{
    printf("fall_handler in context %p\r\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

int main()
{
    // Request the shared queue
    EventQueue *queue = mbed_event_queue();
    printf("Starting in context %p\r\n", ThisThread::get_id());
    // The 'rise' handler will execute in IRQ context
    sw.rise(rise_handler);
    // The 'fall' handler will execute in the context of the shared queue thread
    sw.fall(queue->event(fall_handler));
}
