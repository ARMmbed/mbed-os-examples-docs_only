/*
 * PackageLicenseDeclared: Apache-2.0
 * Copyright (c) 2017 ARM Limited
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

#ifndef _MBED_HTTP_RESPONSE_BUILDER_
#define _MBED_HTTP_RESPONSE_BUILDER_

#include <string>
#include <map>
#include "http_parser.h"
#include "http_parsed_url.h"

class HttpResponseBuilder {
public:
    HttpResponseBuilder(uint16_t a_status_code);

    /**
     * Set a header for the request
     * If the key already exists, it will be overwritten...
     */
    void set_header(string key, string value);
    char *build(const void *body, size_t body_size, size_t *size);
    nsapi_error_t send(TCPSocket *socket, const void *body, size_t body_size);

private:
    uint16_t status_code;
    const char *status_message;
    map<string, string> headers;
};

#endif // _MBED_HTTP_RESPONSE_BUILDER_
