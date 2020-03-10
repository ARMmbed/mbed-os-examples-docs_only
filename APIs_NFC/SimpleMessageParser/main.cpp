/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "nfc/ndef/MessageBuilder.h"
#include "nfc/ndef/common/URI.h"
#include "nfc/ndef/common/Text.h"
#include "nfc/ndef/common/util.h"
#include "nfc/ndef/common/SimpleMessageParser.h"

using mbed::nfc::ndef::Record;
using mbed::nfc::ndef::RecordType;
using mbed::nfc::ndef::RecordID;
using mbed::nfc::ndef::MessageParser;
using mbed::nfc::ndef::common::Text;
using mbed::nfc::ndef::common::URI;
using mbed::nfc::ndef::common::Mime;
using mbed::nfc::ndef::MessageBuilder;
using mbed::nfc::ndef::common::span_from_cstr;
using mbed::nfc::ndef::common::SimpleMessageParser;

int main()
{
    uint8_t message_data[512];
    const Span<uint8_t, 512> buffer(message_data, sizeof(message_data));

    MessageBuilder builder(buffer);

    Text text(Text::UTF8, span_from_cstr("en-US"), span_from_cstr("Mbed website"));
    URI uri(URI::HTTPS_WWW, span_from_cstr("mbed.com"));

    uri.append_as_record(builder);
    text.append_as_record(builder, /* last record */ true);

    SimpleMessageParser parser;
    struct : SimpleMessageParser::Delegate {
        virtual void on_parsing_started()
        {
            printf("parsing started\r\n");
        }

        virtual void on_text_parsed(const Text &text, const RecordID &)
        {
            printf("Text record parsed.\r\n");
            printf(
                "\tlanguage: %.*s\r\n",
                text.get_language_code().size(), text.get_language_code().data()
            );
            printf("\ttext: %.*s\r\n",  text.get_text().size(), text.get_text().data());
        }

        virtual void on_uri_parsed(const URI &uri, const RecordID &)
        {
            printf("URI parsed.\r\n");
            printf("\tid: %d\r\n", uri.get_id());
            printf("\tvalue: %.*s\r\n",  uri.get_uri_field().size(), uri.get_uri_field().data());
        }

        virtual void on_mime_parsed(const Mime &mime, const RecordID &)
        {
            printf("Mime object parsed.\r\n");
            printf("\ttype: %.*s\r\n", mime.get_mime_type().size(), mime.get_mime_type().data());
            printf("\tcontent size: %d\r\n", mime.get_mime_content().size());
        }

        virtual void on_unknown_record_parsed(const Record &record)
        {
            printf("Unknown record parsed.\r\n");
            printf(
                "\ttype: %d, type_value: %.*s\r\n",
                record.type.tnf, record.type.value.size(), record.type.value.data()
            );
            printf(
                "\tpayload size: %d, payload: %.*s\r\n",
                record.payload.size(), record.payload.size(), record.payload.data()
            );
        }

        virtual void on_parsing_terminated()
        {
            printf("parsing terminated\r\n");
        }

        virtual void on_parsing_error(MessageParser::error_t error)
        {
            printf("Parsing error: %d\r\n", error);
        }
    } delegate;

    parser.set_delegate(&delegate);
    parser.parse(buffer);
}
