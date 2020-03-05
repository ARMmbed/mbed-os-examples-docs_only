/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "Kernel.h"

/* Entry function for test thread */
void test_thread(void)
{
    printf("\ntest thread started");
    ThisThread::sleep_for(2000);
    printf("\ntest thread exiting");
}

/* Hook function for thread terminate */
void thread_terminate_hook(osThreadId_t id)
{
    printf("\ntest thread terminated");
}

/* Hook function for idle task */
void test_idle_hook(void)
{
    printf("\nidle hook invoked\n");
    //Now remove this hook and re-instate the original hook by passing a NULL for the idle hook funtion pointer
    Kernel::attach_idle_hook(NULL);
}

// main() runs in its own thread in the OS
int main()
{

    printf("\nattach_thread_terminate_hook demo:\n");

    //Attach a hook for thread terminate event
    Kernel::attach_thread_terminate_hook(thread_terminate_hook);
    Thread *newThread = new Thread(osPriorityNormal1, 1024, NULL, NULL);
    newThread->start(callback(test_thread));
    ThisThread::sleep_for(4000);

    printf("\n\nattach_idle_hook demo:\n");
    //Attach a hook for idle task
    Kernel::attach_idle_hook(test_idle_hook);

    while (1) {
        ThisThread::sleep_for(3000);
    }
    printf("\n\n");
}
