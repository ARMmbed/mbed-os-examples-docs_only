## USBAudio wav audio player example

The example plays the wav audio file from the target's SD card on the host PC over USB.

1. Flash the board, and ensure the target's auxiliary USB is plugged into the PC.
2. Store example audio file on the SD card in the following location: `songs/Bach-minuet-in-g.wav`.
3. Insert SD-card to the targte's SD-card slot.
4. Open a program like Audacity, select microphone(Mbed audio) as an audio source and record sample.
5. Play the recorded sound.

**Note:** This example should work whitout any modifications on the `NXP FRDM-K64F` with SD card connected.
**Note:** You can also route microphone(Mbed audio) to the output device and you should hear the music.