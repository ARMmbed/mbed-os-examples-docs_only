#include "mbed.h"

DigitalOut myled(LED1);

int main()
{
    while (1) {
        myled = 1;
        // printf("LED On\r\n");
        wait(0.2);
        myled = 0;
        // printf("LED Off \r\n");
        wait(0.2);
    }
}
