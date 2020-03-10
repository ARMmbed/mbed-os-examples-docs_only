/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "stdint.h"
#include "NFC.h"
#include "events/EventQueue.h"
#include "nfc/controllers/PN512Driver.h"
#include "nfc/controllers/PN512SPITransportDriver.h"

static uint8_t ndef_buffer[1024] = {0};

int main()
{
    mbed::nfc::PN512SPITransportDriver pn512_transport(D11, D12, D13, D10, A1, A0);
    mbed::nfc::PN512Driver pn512_driver(&pn512_transport);
    events::EventQueue queue;
    mbed::nfc::NFCController nfc(&pn512_driver, &queue, ndef_buffer);

    // ...
}
