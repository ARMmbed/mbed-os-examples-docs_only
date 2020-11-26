#include "mbed.h"
#include "rtos.h"

#define STOP_FLAG 1

// Toggles LED
void blink(DigitalOut *led)
{
    // Toggle the LED every second, until the STOP_FLAG is set
    while (!ThisThread::flags_wait_any_for(STOP_FLAG, 1s)) {
        *led = !*led;
    }
}

// Creates a thread to toggle an LED for 5 seconds
int main()
{
    Thread thread;
    DigitalOut led1(LED1);
    thread.start(callback(blink, &led1));
    // Pause the main thread for 5 seconds
    ThisThread::sleep_for(5s);
    // Set the flag checked by the thread to stop the loop
    thread.flags_set(STOP_FLAG);
    // Wait for the thread to terminate
    thread.join();
}
