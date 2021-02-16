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

#ifndef _HTTP_SERVER_
#define _HTTP_SERVER_

#include "mbed.h"
#include "http_request_parser.h"
#include "http_response.h"
#include "http_response_builder.h"

#ifndef HTTP_SERVER_MAX_CONCURRENT
#define HTTP_SERVER_MAX_CONCURRENT      5
#endif

typedef HttpResponse ParsedHttpRequest;

/**
 * \brief HttpServer implements the logic for setting up an HTTP server.
 */
class HttpServer {
public:
    /**
     * HttpRequest Constructor
     *
     * @param[in] network The network interface
    */
    HttpServer(NetworkInterface *network);

    ~HttpServer();

    /**
     * Start running the server (it will run on it's own thread)
     */
    nsapi_error_t start(uint16_t port, Callback<void(ParsedHttpRequest *request, TCPSocket *socket)> a_handler);

private:

    void receive_data();

    void server_loop();

    void log_server_state(void);

    typedef struct {
        TCPSocket *socket;
        Thread    *thread;
    } socket_thread_metadata_t;

    TCPSocket *server;
    NetworkInterface *_network;
    Thread server_thread;
    vector<TCPSocket *> sockets;
    vector<socket_thread_metadata_t *> socket_threads;
    Callback<void(ParsedHttpRequest *request, TCPSocket *socket)> handler;
    mbed_stats_socket_t stats[MBED_CONF_NSAPI_SOCKET_STATS_MAX_COUNT];
};

#endif // _HTTP_SERVER
