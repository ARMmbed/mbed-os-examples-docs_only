## FileHandle sigio example

The example monitors a serial console device, and every time it reads a character, it sends it back to the console and toggles LED2.

1. Flash the board, and ensure the target's USB is plugged into the PC.
2. Open serial console (select associated COM port, transmission speed: 9600 bps).
3. Reset the target.
4. Every time that device reads a character, the character should appear in the console and LED2 should be toggled.

**Note:** You can check the associated serial port using `mbedls` command.
