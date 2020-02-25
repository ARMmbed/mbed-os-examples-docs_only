// Main thread 
#include "mbed.h"

static DigitalOut led1(LED1);
static DigitalOut led2(LED2);

static BufferedSerial device(STDIO_UART_TX, STDIO_UART_RX);

static void callback_ex()
{
    // always read until data is exhausted - we may not get another
    // sigio otherwise
    while (1) {
        char c;
        if (device.read(&c, 1) != 1) {
            break;
        }
        putchar(c);
        led2 = !led2;
    }
}

int main()
{
    // BufferedSerial-specific method - all others are from FileHandle base class
    device.set_baud(19200);

    // Ensure that device.read() returns -EAGAIN when out of data
    device.set_blocking(false);

    // sigio callback is deferred to event queue, as we cannot in general
    // perform read() calls directly from the sigio() callback.
    device.sigio(mbed_event_queue()->event(callback_ex));

    while (1) {
        led1 = !led1;
        ThisThread::sleep_for(500);
    }
}