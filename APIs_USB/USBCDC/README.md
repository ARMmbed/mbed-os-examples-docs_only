## USBCDC example

The example sends string in the loop using an emulated serial port over USB.

1. Flash the board, and ensure the target's auxiliary USB is plugged into the PC.
2. Open serial console (select associated COM port, transmission speed: 9600 bps).
3. Reset the target.
4. "Hello world" string should appear in the loop on the serial console in the 1-second delays.

**Note:** On Windows you can check the associated COM port in the Device Manager (USB Serial Device).
**Note:** If you want printf functionality, please see the USBSerial class.