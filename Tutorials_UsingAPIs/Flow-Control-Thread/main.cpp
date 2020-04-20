#include "mbed.h"

using namespace std::chrono_literals;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
Thread thread;

void led2_thread()
{
    while (true) {
        led2 = !led2;
        ThisThread::sleep_for(1s);
    }
}

int main()
{
    // Create a thread to execute the function led2_thread
    thread.start(led2_thread);
    // led2_thread is executing concurrently with main at this point

    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(500ms);
    }
}
