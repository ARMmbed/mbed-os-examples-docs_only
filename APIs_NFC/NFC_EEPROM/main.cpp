#include "stdint.h"

#include "NFC.h"
#include "events/EventQueue.h"
#include "m24sr_driver.h"

static uint8_t ndef_buffer[1024] = {0};

int main()
{
    mbed::nfc::vendor::ST::M24srDriver m24sr_driver(D14, D15);
    events::EventQueue queue;
    mbed::nfc::NFCEEPROM nfc(&m24sr_driver, &queue, ndef_buffer);

    // ...
    nfc.write_ndef_message();
}
