## Poll example

The example transfers bidirectional data between two serial ports, acting as a virtual link.

1. Example `mbed_app.json` file (`K64F`):

```
{
    "config": {
        "UART1_TX": "ARDUINO_UNO_D1",
        "UART1_RX": "ARDUINO_UNO_D0",
        "UART2_TX": "USBTX",
        "UART2_RX": "USBRX"
    }
}
```

2. Flash the board, and ensure the target's USB is plugged into the PC (UART2).
3. Connect second serial port to PC via USB to serial adapter (UART1).
4. Open two serial consoles (select associated COM ports, transmission speed: 9600 bps).
5. Reset the target.
6. Data sent from one console should appear in the other one and vice versa.

**Note:** You can check the associated serial port using `mbedls` command (UART2).  
**Note:** Note: On Windows you can check the associated COM port in the Device Manager (UART1).  
**Note:** Please adapt your pins for target different than `K64F`.
