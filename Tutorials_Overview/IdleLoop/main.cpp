#include "mbed.h"
#include "rtos_idle.h"

using namespace std::chrono_literals;

// LED for main thread
DigitalOut led2(LED2);
// LED for idle thread
DigitalOut led1(LED1);
LowPowerTicker watchdogTicker;
Thread watchdogThread;
EventQueue watchdogQueue;

void watchdogRefreshHandler()
{
    led2 = !led2;
};

void watchdogRefreshIsr()
{
    watchdogQueue.call(callback(&watchdogRefreshHandler));
};

void new_idle_loop()
{
    // Executes when no other thread is running
    led1 = !led1;
}

int main()
{

    watchdogThread.start(callback(&watchdogQueue, &EventQueue::dispatch_forever));
    watchdogTicker.attach(callback(&watchdogRefreshIsr), 5s);
    rtos_attach_idle_hook(&new_idle_loop);
}
