#include "mbed.h"
#include "USBMIDI.h"

USBMIDI midi;

int main()
{
    while (1) {
        for (int i = 48; i < 83; i++) { // send some messages!
            midi.write(MIDIMessage::NoteOn(i));
            ThisThread::sleep_for(250);
            midi.write(MIDIMessage::NoteOff(i));
            ThisThread::sleep_for(500);
        }
    }
}