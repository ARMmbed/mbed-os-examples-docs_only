/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// Globals
DigitalOut alarm_out(D2, 0);
DigitalOut alarm_led(LED1, 1);
DigitalOut hour_led(LED2, 1);
DigitalOut min_led(LED3, 1);

InterruptIn inc_time(BUTTON1);
InterruptIn sel(BUTTON2);

LowPowerTicker alarm_event;

std::chrono::hours hour_inc;
std::chrono::minutes min_inc;

volatile uint8_t select_state = 0;

// Timer Callbacks
void inc_select(void)
{
    if (select_state < 2) {
        select_state++;
    } else {
        // Use select button to disable alarm
        alarm_out = 0;
        alarm_led = 1;
    }
}

void set_time_leds(void)
{
    if (select_state == 0) {
        hour_led = !hour_led;
    } else {
        min_led = !min_led;
    }
}

void inc_delay(void)
{
    if (select_state == 0) {
        hour_inc++;
        hour_led = !hour_led;
    } else {
        min_inc++;
        min_led = !min_led;
    }
}

void trigger_alarm_out(void)
{
    alarm_out = 1;
    alarm_led = 0;
}

/* Use buttons to select the alarm time. Cycle through hours in an incrementing
 * fashion using Button1. Press select, and increment through minutes. Press
 * select one more time to begin the alarm timer.
 *
 * The Time LEDs blink in time with the button inputs to show the
 * currently selected alarm time. Once you press select a second time to begin
 * the timer, the LEDs will blink out the configured delay in hours and
 * minutes before going into a low power sleep mode.
 *
 * Once the alarm fires, pressing the select button will turn the alarm off
 * until the next time it fires.
 *__________________________________________________________________________
 * You may also use the RTC (hardware or software through the Time API) to
 * set a real world time and set an alarm for a specific timestamp rather
 * than on a delay. However, this requires manually setting the time on each
 * reset, or an internet connection to automatically collect the
 * time.
 */
// Main thread
int main()
{
    // Configure interrupt in pins (button controls)
    sel.rise(inc_select);
    inc_time.fall(set_time_leds);
    inc_time.rise(inc_delay);

    // Sleep while waiting for user input to set the desired delay
    while (select_state < 2) {
        ThisThread::sleep_for(10ms);
    }

    // Once the delay has been input, blink back the configured hours and
    // minutes selected
    for (uint8_t i = 0; i < hour_inc.count() * 2; i++) {
        hour_led = !hour_led;
        ThisThread::sleep_for(250ms);
    }

    for (uint8_t i = 0; i < min_inc.count() * 2; i++) {
        min_led = !min_led;
        ThisThread::sleep_for(250ms);
    }

    // Attach the low power ticker with the configured alarm delay
    auto delay = hour_inc + min_inc;
    alarm_event.attach(&trigger_alarm_out, delay);

    // Sleep in the main thread
    while (1) {
        sleep();
    }
}
