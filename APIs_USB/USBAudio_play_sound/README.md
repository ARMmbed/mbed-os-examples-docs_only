## USBAudio play sound example

The example loads raw audio data to your board's flash and then plays on the host PC over USB.

1. Flash the board, and ensure the target's auxiliary USB is plugged into the PC.
2. Open a program like Audacity, select microphone(Mbed audio) as an audio source and record sample.
3. Play the the recorded sound.

**Note:** This example should work whitout any modifications on the `NXP FRDM-K64F`, which has `1 MB` of flash memory.
**Note:** If you are using a board that has less than `1 MB` of flash memory, delete data from the end of the `data` array, and set `NUM_ELEMENTS` accordingly until the program size is small enough to flash without exceeding storage.
