## USBHID example

This example turns the Mbed board into the HID (Human Interface Device) that can send and receive messages over USB.

1. Flash the board, and ensure the target's auxiliary USB is plugged into the PC.
2. Open serial console (select Mbed COM port, transmission speed: 9600 bps).
3. Reset the target.
4. Run the attached Python script.
5. The script will send 8 bytes of data (1 2 3 4 5 6 7 8) to the Mbed board and will read and print the data sent to the host computer by the Mbed board.
6. You should see "1 2 3 4 5 6 7 8" on the console and LED1 on the target device should change its state to the opposite.

**Note:** You can check the Mbed COM port using "mbedls" command.