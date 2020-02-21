#include "mbed.h"

static DigitalOut led2(LED2);

// UARTSerial derives from FileHandle
static UARTSerial device(STDIO_UART_TX, STDIO_UART_RX);

int main()
{
    // Perform device-specific setup
    device.set_baud(19200);

    // Once set up, access through the C library
    FILE *devin = fdopen(&device, "r");

    while (1) {
        putchar(fgetc(devin));
        led2 = !led2;
    }
}
