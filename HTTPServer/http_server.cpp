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

#include "http_server.h"

HttpServer::HttpServer(NetworkInterface *network) : _network(network)
{
    _network = network;
}

HttpServer::~HttpServer()
{
    for (size_t ix = 0; ix < HTTP_SERVER_MAX_CONCURRENT; ix++) {
        if (socket_threads[ix]) {
            delete socket_threads[ix];
        }
    }
}

nsapi_error_t HttpServer::start(uint16_t port, Callback<void(ParsedHttpRequest *request, TCPSocket *socket)> a_handler)
{
    server = new TCPSocket();

    nsapi_error_t ret;

    ret = server->open(_network);
    if (ret != NSAPI_ERROR_OK) {
        return ret;
    }

    ret = server->bind(port);
    if (ret != NSAPI_ERROR_OK) {
        return ret;
    }

    ret = server->listen(HTTP_SERVER_MAX_CONCURRENT);
    if (ret != NSAPI_ERROR_OK) {
        return ret;
    }

    handler = a_handler;

    server_thread.start(callback(this, &HttpServer::server_loop));

    return NSAPI_ERROR_OK;
}

void HttpServer::receive_data()
{
    TCPSocket *socket = sockets.back();

    // needs to keep running until the socket gets closed
    while (1) {

        ParsedHttpRequest *response = new ParsedHttpRequest();
        HttpParser *parser = new HttpParser(response, HTTP_REQUEST);

        // Set up a receive buffer (on the heap)
        uint8_t *recv_buffer = (uint8_t *)malloc(HTTP_RECEIVE_BUFFER_SIZE);

        // TCPSocket::recv is called until we don't have any data anymore
        nsapi_size_or_error_t recv_ret;
        while ((recv_ret = socket->recv(recv_buffer, HTTP_RECEIVE_BUFFER_SIZE)) > 0) {
            // Pass the chunk into the http_parser
            int32_t nparsed = parser->execute((const char *)recv_buffer, recv_ret);
            if (nparsed != recv_ret) {
                printf("Parsing failed... parsed %ld bytes, received %d bytes\n", nparsed, recv_ret);
                recv_ret = -2101;
                break;
            }

            if (response->is_message_complete()) {
                break;
            }
        }

        if (recv_ret <= 0) {
            if (recv_ret < 0) {
                printf("Error reading from socket %d\n", recv_ret);
            }

            // error = recv_ret;
            delete response;
            delete parser;
            free(recv_buffer);

            return;
        }

        // When done, call parser.finish()
        parser->finish();

        // Free the receive buffer
        free(recv_buffer);

        // Let user application handle the request, if user needs a handle to response they need to memcpy themselves
        if (recv_ret > 0) {
            handler(response, socket);
        }

        // Free the response and parser
        delete response;
        delete parser;
    }
}

void HttpServer::server_loop()
{
    while (1) {
        TCPSocket *clt_sock = server->accept();
        if (clt_sock) {
            log_server_state();

            sockets.push_back(clt_sock); // so we can clear our disconnected sockets

            // and start listening for events there
            Thread *t = new Thread(osPriorityNormal, 2048, NULL, NULL);
            t->start(callback(this, &HttpServer::receive_data));

            socket_thread_metadata_t *m = new socket_thread_metadata_t();
            m->socket = clt_sock;
            m->thread = t;
            socket_threads.push_back(m);
        } else {
            delete clt_sock;
        }

        for (size_t ix = 0; ix < socket_threads.size(); ix++) {
            if ((uint32_t)osThreadGetState(socket_threads[ix]->thread->get_id()) == osThreadTerminated) {
                printf("Thread Deleted\r\n");
                socket_threads[ix]->thread->terminate();
                socket_threads[ix]->socket->close();
                delete socket_threads[ix]->thread;
                socket_threads.erase(socket_threads.begin() + ix);
            }
        }

    }
}

void HttpServer::log_server_state(void)
{
    uint8_t count = SocketStats::mbed_stats_socket_get_each(&stats[0], MBED_CONF_NSAPI_SOCKET_STATS_MAX_COUNT);
    printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ID", "State", "Proto", "Sent", "Recv", "Time");

    for (int i = 0; i < count; i++) {
        printf("%-15p", stats[i].reference_id);

        switch (stats[i].state) {
            case SOCK_CLOSED:
                printf("%-15s", "Closed");
                break;
            case SOCK_OPEN:
                printf("%-15s", "Open");
                break;
            case SOCK_CONNECTED:
                printf("%-15s", "Connected");
                break;
            case SOCK_LISTEN:
                printf("%-15s", "Listen");
                break;
            default:
                printf("%-15s", "Error");
                break;
        }

        if (NSAPI_TCP == stats[i].proto) {
            printf("%-15s", "TCP");
        } else {
            printf("%-15s", "UDP");
        }
        printf("%-15d", stats[i].sent_bytes);
        printf("%-15d", stats[i].recv_bytes);
        printf("%-15lld\n", stats[i].last_change_tick);
    }
}
