#include "mbed.h"

using namespace std::chrono_literals;

InterruptIn button(BUTTON1);
DigitalOut led(LED1);
DigitalOut heartbeat(LED2);

void toggle()
{
    led = !led;
}

int main()
{
    button.rise(&toggle);  // call toggle function on the rising edge
    while (1) {            // wait around, interrupts will interrupt this!
        heartbeat = !heartbeat;
        ThisThread::sleep_for(250ms);
    }
}
