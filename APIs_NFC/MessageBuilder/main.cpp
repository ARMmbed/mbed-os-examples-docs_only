/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "nfc/ndef/MessageBuilder.h"
#include "nfc/ndef/common/URI.h"
#include "nfc/ndef/common/Text.h"
#include "nfc/ndef/common/util.h"

using mbed::nfc::ndef::MessageBuilder;
using mbed::nfc::ndef::common::Text;
using mbed::nfc::ndef::common::URI;
using mbed::nfc::ndef::common::span_from_cstr;

int main()
{
    uint8_t message_data[128];
    const Span<uint8_t, 128> buffer(message_data, sizeof(message_data));

    MessageBuilder builder(buffer);

    URI uri(URI::HTTPS_WWW, span_from_cstr("mbed.com"));
    Text text(Text::UTF8, span_from_cstr("en-US"), span_from_cstr("Mbed website"));

    uri.append_as_record(builder);
    text.append_as_record(builder, /* last record */ true);

    printf("Message size: %d bytes\r\n",  builder.get_message().size());
}
