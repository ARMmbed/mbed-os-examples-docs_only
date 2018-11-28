#include "mbed.h"
#include "http_server.h"
#include "http_response_builder.h"
#include "webpage.h"

DigitalOut led(LED1);
bool stats_enabled = false;

static uint8_t max_thread_count = 16;
mbed_stats_thread_t *thread_stats = new mbed_stats_thread_t[max_thread_count];

void report_thread_stats(void)
{
    printf("================ THREAD STATS ===============\r\n");
    // Collect and print running thread stats
    int count = mbed_stats_thread_get_each(thread_stats, max_thread_count);

    for (int i = 0; i < count; i++) {
        printf("Name: %s \r\n",         thread_stats[i].name);
        printf("State: %ld \r\n",       thread_stats[i].state);
        printf("Stack Space: %ld \r\n", thread_stats[i].stack_space);
    }
}

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
    } else if (request->get_method() == HTTP_POST && request->get_url() == "/stats") {
        report_thread_stats();

        HttpResponseBuilder builder(200);
        builder.send(socket, NULL, 0);
    } else {
        HttpResponseBuilder builder(404);
        builder.send(socket, NULL, 0);
    }
}

int main()
{
    printf("Running...3.0\r\n");

    // Connect to the network (see mbed_app.json for the connectivity method used)
    NetworkInterface *network = NetworkInterface::get_default_instance();
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
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
