/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBMIDI.h"

using namespace std::chrono_literals;

#define REST -1
#define C  0
#define Cs 1
#define D  2
#define Ds 3
#define E  4
#define F  5
#define Fs 6
#define G  7
#define Gs 8
#define A  9
#define As 10
#define B  11

#define OCTAVE0  0
#define OCTAVE1  12
#define OCTAVE2  24
#define OCTAVE3  36
#define OCTAVE4  48
#define OCTAVE5  60
#define OCTAVE6  72
#define OCTAVE7  84

#define WHOLE_NOTE     1150ms
#define HALF_NOTE      (WHOLE_NOTE / 2)
#define QUARTER_NOTE   (WHOLE_NOTE / 4)
#define EIGHTH_NOTE    (WHOLE_NOTE / 8)
#define SIXTEENTH_NOTE (WHOLE_NOTE / 16)

#define THREE_EIGHTHS_NOTE   (EIGHTH_NOTE * 3)
#define THREE_FORTHS_NOTE   (QUARTER_NOTE * 3)

USBMIDI midi;

void PlayNote(int note, int octave, chrono::milliseconds duration)
{
    if (note == REST) {
        ThisThread::sleep_for(duration);
    } else {
        midi.write(MIDIMessage::NoteOn(note + octave));
        ThisThread::sleep_for(duration);
        midi.write(MIDIMessage::NoteOff(note + octave));
    }
}

void TakeMeOutToTheBallGame()
{
    //https://www.bethsnotesplus.com/2012/09/take-me-out-to-ball-game.html
    PlayNote(C, OCTAVE5, HALF_NOTE);
    PlayNote(C, OCTAVE6, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(G, OCTAVE5, QUARTER_NOTE);
    PlayNote(E, OCTAVE5, QUARTER_NOTE);

    PlayNote(G, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(D, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(C, OCTAVE5, HALF_NOTE);
    PlayNote(C, OCTAVE6, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(G, OCTAVE5, QUARTER_NOTE);
    PlayNote(E, OCTAVE5, QUARTER_NOTE);

    PlayNote(G, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(G, OCTAVE5, HALF_NOTE);
    PlayNote(REST, 0, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(Gs, OCTAVE5, QUARTER_NOTE);
    PlayNote(A, OCTAVE5, QUARTER_NOTE);

    PlayNote(E, OCTAVE5, QUARTER_NOTE);
    PlayNote(F, OCTAVE5, QUARTER_NOTE);
    PlayNote(G, OCTAVE5, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, HALF_NOTE);
    PlayNote(F, OCTAVE5, QUARTER_NOTE);

    PlayNote(D, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(A, OCTAVE5, HALF_NOTE);
    PlayNote(A, OCTAVE5, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(B, OCTAVE5, QUARTER_NOTE);
    PlayNote(C, OCTAVE6, QUARTER_NOTE);

    PlayNote(D, OCTAVE6, QUARTER_NOTE);
    PlayNote(B, OCTAVE5, QUARTER_NOTE);
    PlayNote(A, OCTAVE5, QUARTER_NOTE);

    PlayNote(G, OCTAVE5, QUARTER_NOTE);
    PlayNote(E, OCTAVE5, QUARTER_NOTE);
    PlayNote(D, OCTAVE5, QUARTER_NOTE);

    PlayNote(C, OCTAVE5, HALF_NOTE);
    PlayNote(C, OCTAVE6, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(G, OCTAVE5, QUARTER_NOTE);
    PlayNote(E, OCTAVE5, QUARTER_NOTE);

    PlayNote(G, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(D, OCTAVE5, HALF_NOTE);
    PlayNote(D, OCTAVE5, QUARTER_NOTE);

    PlayNote(C, OCTAVE5, HALF_NOTE);
    PlayNote(D, OCTAVE5, QUARTER_NOTE);

    PlayNote(E, OCTAVE5, QUARTER_NOTE);
    PlayNote(F, OCTAVE5, QUARTER_NOTE);
    PlayNote(G, OCTAVE5, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(A, OCTAVE5, QUARTER_NOTE);
    PlayNote(B, OCTAVE5, QUARTER_NOTE);

    PlayNote(C, OCTAVE6, THREE_FORTHS_NOTE);

    PlayNote(C, OCTAVE6, THREE_FORTHS_NOTE);

    PlayNote(C, OCTAVE6, QUARTER_NOTE);
    PlayNote(B, OCTAVE5, QUARTER_NOTE);
    PlayNote(A, OCTAVE5, QUARTER_NOTE);

    PlayNote(G, OCTAVE5, QUARTER_NOTE);
    PlayNote(Fs, OCTAVE5, QUARTER_NOTE);
    PlayNote(G, OCTAVE5, QUARTER_NOTE);

    PlayNote(A, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(B, OCTAVE5, THREE_FORTHS_NOTE);

    PlayNote(C, OCTAVE6, THREE_FORTHS_NOTE);

    PlayNote(C, OCTAVE6, HALF_NOTE);
    PlayNote(REST, 0, QUARTER_NOTE);
}

int main()
{
    while (1) {
        TakeMeOutToTheBallGame();
    }
}
