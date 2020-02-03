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
    serial_obj.baud(19200);
    printf("Hello World!\n");
}
