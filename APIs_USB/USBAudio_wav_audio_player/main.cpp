// Mbed WAV Audio Player
#include "mbed.h"
#include "USBAudio.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "AudioPlayer.h"
#include "WaveAudioStream.h"

#define BUFFER_SIZE 512
#define FREQ_25_MHZ 25000000

// Connection for SD card
SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);//MOSI, MISO, SCLK, CS
FATFileSystem fs("sd", &sd);

int main()
{
    // Set the maximum speed so it can keep up with audio
    sd.frequency(FREQ_25_MHZ);
    // Load WAV file from SD card
    // WAV file must be PCM signed 16-bit little endian
    File file;
    if (file.open(&fs, "songs/Bach-minuet-in-g.wav") != 0) {
        error("Could not open 'songs/Bach-minuet-in-g.wav'\r\n");
    }
    WaveAudioStream song(&file);//"song" is the audio data object
    // Check to see if file is a valid WAV file
    if (song.get_valid() == 0) {
        error("ERROR: not valid WAV file\r\n");
    }
    // WAV file must be 16-bit
    if (song.get_bytes_per_sample() != 2) {
        error("ERROR: WAV file not 2 bytes per sample (16-bit)\r\n");
    }
    USBAudio audio(true, 8000, song.get_channels(), song.get_sample_rate(), song.get_channels());
    uint8_t buffer[BUFFER_SIZE];
    int num_bytes_read;
    printf("Playing Audio\r\n");
    // Reads and plays data from WAV file over USB until song is over
    while (1) {
        num_bytes_read = song.read(buffer, BUFFER_SIZE);
        if (num_bytes_read == -1) {
            printf("Song Over\r\n");
            break;
        }
        audio.write(buffer, num_bytes_read);
    }
    song.close();//Close the WAV file
}
