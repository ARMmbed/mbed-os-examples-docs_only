# BusOut example

You can use the BusOut interface to create an artificial bus of pins out of any digital ins. The pins don't need sequential hardware addressing. This example program counts up from 0 to 15 or binary 0000 to 1111. The effect of this is turning LED1-LED4 on or off according to the number going across the bus. The example code toggles LEDs on and off. If a tricolor LED is on the board, the LED changes colors. 

**Note**: When initializing a BusOut object, you initialize pins in their bit order from right to left. Be careful because the bit order is the reverse of the object initializing order.

| Integer | binary | LED On(1) / Off(0)
| ------- | ------ | ------------------
|  0 | 0000 | LED4=0 LED3=0 LED2=0 LED1=0
|  1 | 0001 | LED4=0 LED3=0 LED2=0 LED1=1
|  2 | 0010 | LED4=0 LED3=0 LED2=1 LED1=
|  3 | 0011 | LED4=0 LED3=0 LED2=1 LED1=1
|  4 | 0100 | LED4=0 LED3=1 LED2=0 LED1=0
|  5 | 0101 | LED4=0 LED3=1 LED2=0 LED1=1
|  6 | 0110 | LED4=0 LED3=1 LED2=1 LED1=0
|  7 | 0111 | LED4=0 LED3=1 LED2=1 LED1=1
|  8 | 1000 | LED4=1 LED3=0 LED2=0 LED1=0
|  9 | 1001 | LED4=1 LED3=0 LED2=0 LED1=1
| 10 | 1010 | LED4=1 LED3=0 LED2=1 LED1=0
| 11 | 1011 | LED4=1 LED3=0 LED2=1 LED1=1
| 12 | 1100 | LED4=1 LED3=1 LED2=0 LED1=0
| 13 | 1101 | LED4=1 LED3=1 LED2=0 LED1=1
| 14 | 1110 | LED4=1 LED3=1 LED2=1 LED1=0
| 15 | 1111 | LED4=1 LED3=1 LED2=1 LED1=1
