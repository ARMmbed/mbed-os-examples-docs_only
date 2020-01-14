// Audio loopback example use:
// 1. Flash the board, and ensure the target's auxiliary USB is plugged into the PC.
// 2. Select "Mbed Audio" as your PC's default speaker and microphone devices.
// 3. Play some sound (YouTube, audio file, etc.) on your PC.
// 4. The audio that is playing on your PC will be recorded by Audacity via USB loopback.
#include "mbed.h"
#include "USBAudio.h"

int main() {

    USBAudio audio(true, 44100, 2, 44100, 2);

    printf("Looping audio\r\n");
    static uint8_t buf[128];
    while (true) {
        if (!audio.read(buf, sizeof(buf))) {
            memset(buf, 0, sizeof(buf));
        }
        audio.write(buf, sizeof(buf));
    }
}
