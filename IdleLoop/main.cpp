#include "mbed.h"
#include "rtos_idle.h"

DigitalOut led(LED2);
DigitalOut led1(LED1);
LowPowerTicker watchdogTicker;
Thread watchdogThread;
EventQueue watchdogQueue;


//if we use Serial as a CLI console . The CLI thread allways get the read lock , if another thread want to print something to serial console, it will be blocked by CLI thread .

void watchdogRefreshHandler() {
    led = !led;
    // target-specific feed function
};

void watchdogRefreshIsr() {
    watchdogQueue.call(callback(&watchdogRefreshHandler));
};

void new_idle_loop()
{
	led1 = !led1;
}

int main() {
	watchdogThread.start(callback(&watchdogQueue, &EventQueue::dispatch_forever));
    watchdogTicker.attach(callback(&watchdogRefreshIsr), 5);
    rtos_attach_idle_hook(&new_idle_loop);
}
