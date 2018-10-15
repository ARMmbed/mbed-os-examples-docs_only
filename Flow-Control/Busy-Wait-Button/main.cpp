#include "mbed.h"

DigitalIn button(SW1); // Change to match your board
DigitalOut led(LED1);

#define button_press 0

int main() {
    while(1) {
        if(button_press == button){
           led = !led;
           wait(1);
       }
    }
}
