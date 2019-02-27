/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "http_server.h"
#include "http_response_builder.h"
#include "webpage.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

DigitalOut led(LED1);
bool stats_enabled = false;

static uint8_t max_thread_count = 16;
mbed_stats_thread_t *thread_stats = new mbed_stats_thread_t[max_thread_count];

// Requests come in here
void request_handler(ParsedHttpRequest *request, TCPSocket *socket)
{
    printf("Request came in: %s %s\n", http_method_str(request->get_method()), request->get_url().c_str());

    if (request->get_method() == HTTP_GET && request->get_url() == "/") {
        HttpResponseBuilder builder(200);
        builder.set_header("Content-Type", "text/html; charset=utf-8");

        builder.send(socket, response, sizeof(response) - 1);
    } else if (request->get_method() == HTTP_POST && request->get_url() == "/toggle") {
        printf("toggle LED called\n");
        led = !led;

        HttpResponseBuilder builder(200);
        builder.send(socket, NULL, 0);
    } else if (request->get_method() == HTTP_GET && request->get_url() == "/api/stats") {
        // create JSON object with information about the thread statistics
        rapidjson::Document document;
        document.SetArray();

        int count = mbed_stats_thread_get_each(thread_stats, max_thread_count);
        for (int i = 0; i < count; i++) {
            Value thread_info(kObjectType);
            Value thread_name;
            thread_name.SetString(thread_stats[i].name, strlen(thread_stats[i].name), document.GetAllocator());

            thread_info.AddMember("name", thread_name, document.GetAllocator());
            thread_info.AddMember("state", static_cast<int>(thread_stats[i].state), document.GetAllocator());
            thread_info.AddMember("stack_space", static_cast<int>(thread_stats[i].stack_space), document.GetAllocator());
            document.PushBack(thread_info, document.GetAllocator());
        }

        StringBuffer strbuf;
        Writer<StringBuffer> writer(strbuf);
        document.Accept(writer);

        HttpResponseBuilder builder(200);
        builder.set_header("Content-Type", "application/json");
        builder.send(socket, strbuf.GetString(), strbuf.GetSize());
    } else {
        char resp[512];
        int resp_length = snprintf(resp, sizeof(resp), "Page not found: '%s'", request->get_url().c_str());

        HttpResponseBuilder builder(404);
        builder.send(socket, resp, resp_length);
    }
}

int main()
{
    printf("Connecting to network...\r\n");

    // Connect to the network with the default network interface
    // If you use a shield or an external module you need to replace this line
    // and load the driver yourself. See https://os.mbed.com/docs/mbed-os/v5.11/reference/ip-networking.html
    NetworkInterface *network = NetworkInterface::get_default_instance();
    if (!network) {
        printf("Could not find default network instance\n");
        return 1;
    }

    nsapi_error_t connect_status = network->connect();
    if (connect_status != NSAPI_ERROR_OK) {
        printf("Could not connect to network\n");
        return 1;
    }

    HttpServer server(network);
    nsapi_error_t res = server.start(8080, &request_handler);

    if (res == NSAPI_ERROR_OK) {
        printf("Server is listening at http://%s:8080\n", network->get_ip_address());
    } else {
        printf("Server could not be started... %d\n", res);
    }

    wait(osWaitForever);
}
