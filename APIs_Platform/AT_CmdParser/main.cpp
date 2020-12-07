/* ATCmdParser usage example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"

#define   ESP8266_DEFAULT_BAUD_RATE   115200

int main()
{
    BufferedSerial *_serial;
    ATCmdParser *_parser;

    printf("\nATCmdParser with ESP8266 example");

    _serial = new BufferedSerial(D1, D0, ESP8266_DEFAULT_BAUD_RATE);
    _parser = new ATCmdParser(_serial, "\r\n");
    _parser->debug_on(true);

    //Now get the FW version number of ESP8266 by sending an AT command
    printf("\nATCmdParser: Retrieving FW version");
    _parser->send("AT+GMR");
    int version;
    if (_parser->recv("OK") && _parser->recv("SDK version:%d", &version)) {
        printf("\nATCmdParser: FW version: %d", version);
        printf("\nATCmdParser: Retrieving FW version successful");
    } else {
        printf("\nATCmdParser: Retrieving FW version failed");
        return -1;
    }
}
