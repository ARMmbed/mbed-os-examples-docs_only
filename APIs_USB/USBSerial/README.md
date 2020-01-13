## USBSerial example

The example sends string in loop using emulated serial port over USB.

1. Flash the board, and ensure the target's auxiliary USB is plugged into the PC.
2. Open serial console (select associated COM port, transmission speed: 9600 bps).
3. Reset the target.
4. "I am a virtual serial port" string should appear in loop on the serial console in the 1 second delays.

**Note:** On Windows you can check the associated COM port in the Device Manager (USB Serial Device).
