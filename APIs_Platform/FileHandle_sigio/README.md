## FileHandle sigio example

The example monitors a serial console device, and every time it outputs a character, send it to the console back and toggle LED2.

1. Flash the board, and ensure the target's USB is plugged into the PC.
2. Open serial console (select associated COM port, transmission speed: 19200 bps).
3. Reset the target.
4. Every time that device outputs a character, the character should appear in the console and LED2 should be toggled LED2.

**Note:** You can check the associated serial port using `mbedls` command.
