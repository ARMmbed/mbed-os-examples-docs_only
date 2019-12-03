#include "mbed.h"

DigitalOut myled(LED1);

int main()
{
    while (1) {
        myled = 1;
        // printf("LED On\r\n");
        wait_us(200000);
        myled = 0;
        // printf("LED Off \r\n");
        wait_us(200000);
    }
}
