#include "mbed.h"
#include "USBCDC.h"

USBCDC cdc;

int main(void)
{

    while (1) {
        char msg[] = "Hello world\r\n";
        cdc.send((uint8_t *)msg, strlen(msg));
        ThisThread::sleep_for(1000);
    }
}
