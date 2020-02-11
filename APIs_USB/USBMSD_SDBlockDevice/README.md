## USBMSD SDBlockDevice example

This example turns the Mbed board into the mass storage device (SDBlockDevice).

1. Flash the board.
2. Insert SD-card to the target's SD-card slot.
3. Reset the target.
4. USB mass storage drive should appear in your file explorer.
5. You should be able to access files on this drive.

**Note:** This example should work without any modifications on the `K64F` target.
**Note:** On other targets please update pins used to create `SDBlockDevice` object to be consistent with your board.
**Note:** Please try to connect board directly to the PC (without USB hub) if you encountered some problems with this example.
