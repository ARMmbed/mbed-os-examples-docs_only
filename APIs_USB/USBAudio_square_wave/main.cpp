/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "USBAudio.h"
#include <math.h>

int16_t square_wave(uint32_t freq_hz, uint16_t amplitude, float time_s)
{
    float period = (float)1 / freq_hz;
    if (fmod(time_s, period) > period / 2) {
        return amplitude / 2;
    } else {
        return -(amplitude / 2);
    }
}

int main()
{
    uint32_t tx_freq = 16000;
    USBAudio audio(true, 8000, 2, tx_freq, 1, 10, 0x7bb8, 0x1112, 0x0100);
    float cur_time = 0;
    while (true) {
        uint16_t samples[64];
        for (int i = 0; i < 64; i++) {
            samples[i] = square_wave(100, 5000, cur_time);
            cur_time += 1.0 / tx_freq;
        }
        if (!audio.write((uint8_t *)&samples, sizeof(samples))) {
            audio.write_wait_ready();
        }
    }
}