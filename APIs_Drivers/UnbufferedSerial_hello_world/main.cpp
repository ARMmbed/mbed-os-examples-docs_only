#include <stdio.h>
#include "mbed.h"


static UnbufferedSerial serial_obj(USBTX, USBRX);

// Provide the serial object as the FileHandle for the console
FileHandle *mbed::mbed_override_console(int fd)
{
    return &serial_obj;
}


int main()
{
    // The system I/O retarget code uses serial_obj underneath.
    printf("Hello World!\n");

    while(1) {
        // Echo the inout back to the terminal.
        putc(getc(stdout), stdout);
    }
}
