#include <stdio.h>
#include "mbed.h"


#define BLINKING_RATE_MS                                                    500

static DigitalOut led_status(LED1);
static DigitalOut led_serial_read(LED2);
static UnbufferedSerial serial_obj(USBTX, USBRX);

// Provide the serial object as the FileHandle for the console
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_obj;
}


void on_rx_pin_interrupt()
{
    // Read the serial port to clear the RX interrupt
    putc(getc(stdout), stdout);
    led_serial_read = !led_serial_read;
}


int main()
{
    // Default to interrupt on RX pin
    serial_obj.attach(&on_rx_pin_interrupt);

    while(1) {
        led_status = !led_status;
        thread_sleep_for(BLINKING_RATE_MS);
    }
}
