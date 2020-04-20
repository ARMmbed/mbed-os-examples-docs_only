/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBMIDI.h"

using namespace std::chrono_literals;

USBMIDI midi;

int main()
{
    while (1) {
        for (int i = 48; i < 83; i++) { // send some messages!
            midi.write(MIDIMessage::NoteOn(i));
            ThisThread::sleep_for(250ms);
            midi.write(MIDIMessage::NoteOff(i));
            ThisThread::sleep_for(500ms);
        }
    }
}
