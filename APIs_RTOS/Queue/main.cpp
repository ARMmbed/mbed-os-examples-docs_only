/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

using namespace std::chrono_literals;

typedef struct {
    float    voltage;   /* AD result of measured voltage */
    float    current;   /* AD result of measured current */
    uint32_t counter;   /* A counter value               */
} message_t;

MemoryPool<message_t, 16> mpool;
Queue<message_t, 16> queue;
Thread thread;

/* Send Thread */
void send_thread(void)
{
    uint32_t i = 0;
    while (true) {
        i++; // fake data update
        message_t *message = mpool.alloc();
        message->voltage = (i * 0.1) * 33;
        message->current = (i * 0.1) * 11;
        message->counter = i;
        queue.put(message);
        ThisThread::sleep_for(1s);
    }
}

int main(void)
{
    thread.start(callback(send_thread));

    while (true) {
        osEvent evt = queue.get();
        if (evt.status == osEventMessage) {
            message_t *message = (message_t *)evt.value.p;
            printf("\nVoltage: %.2f V\n\r", message->voltage);
            printf("Current: %.2f A\n\r", message->current);
            printf("Number of cycles: %u\n\r", message->counter);

            mpool.free(message);
        }
    }
}
