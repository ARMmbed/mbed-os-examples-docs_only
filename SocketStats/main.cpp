#include "mbed.h"

#if !defined(MBED_CONF_NSAPI_SOCKET_STATS_ENABLE) 
#error [NOT_SUPPORTED] Socket Statistics not supported
#endif

#define SAMPLE_TIME     10 // milli-sec

void print_stats()
{
    mbed_stats_socket_t stats[MBED_CONF_NSAPI_SOCKET_STATS_MAX_COUNT] = {0};
    static int num = 0;
    int count;
    
    printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Num", "ID", "State", "Proto", "Sent", "Recv", "Time");
    while (1) {

        count = SocketStats::mbed_stats_socket_get_each(&stats[0], MBED_CONF_NSAPI_SOCKET_STATS_MAX_COUNT);
        for (int i = 0; i < count; i++) {
            printf("%-15d", num);
            printf("%-15p", stats[i].reference_id);

            switch (stats[i].state) {
            case SOCK_CLOSED:
                printf("%-15s", "Closed"); break;
            case SOCK_OPEN:
                printf("%-15s", "Open"); break;
            case SOCK_CONNECTED:
                printf("%-15s", "Connected"); break;
            case SOCK_LISTEN:
                printf("%-15s", "Listen"); break;
            default:
                printf("%-15s", "Error"); break;
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
        num++;
        ThisThread::sleep_for(SAMPLE_TIME);
    }
}


// Network interface
NetworkInterface *net;

int main()
{
    Thread *thread = new Thread(osPriorityNormal1, 2048);
    int remaining;
    int rcount;
    char *p;
    char *buffer = new char[256];
    nsapi_size_or_error_t result;

    thread->start(print_stats);
    // Bring up the ethernet interface
    printf("Mbed OS Socket example\n");

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    net = NetworkInterface::get_default_instance();

    if (!net) {
        printf("Error! No network inteface found.\n");
        return 0;
    }

    result = net->connect();
    if (result != 0) {
        printf("Error! net->connect() returned: %d\n", result);
        return result;
    }

    // Show the network address
    const char *ip = net->get_ip_address();
    const char *netmask = net->get_netmask();
    const char *gateway = net->get_gateway();
    printf("IP address: %s\n", ip ? ip : "None");
    printf("Netmask: %s\n", netmask ? netmask : "None");
    printf("Gateway: %s\n", gateway ? gateway : "None");

    // Open a socket on the network interface, and create a TCP connection to api.ipify.org
    TCPSocket socket;
    // Send a simple http request
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: api.ipify.org\r\nConnection: close\r\n\r\n";
    nsapi_size_t size = strlen(sbuffer);

    result = socket.open(net);
    if (result != 0) {
        printf("Error! socket.open() returned: %d\n", result);
    }

    result = socket.connect("api.ipify.org", 80);
    if (result != 0) {
        printf("Error! socket.connect() returned: %d\n", result);
        goto DISCONNECT;
    }

    // Loop until whole request sent
    while(size) {
        result = socket.send(sbuffer+result, size);
        if (result < 0) {
            printf("Error! socket.send() returned: %d\n", result);
            goto DISCONNECT;
        }
        size -= result;
        printf("sent %d [%.*s]\n", result, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);
    }

    // Receieve an HTTP response and print out the response line
    remaining = 256;
    rcount = 0;
    p = buffer;
    while (0 < (result = socket.recv(p, remaining))) {
        p += result;
        rcount += result;
        remaining -= result;
    }
    if (result < 0) {
        printf("Error! socket.recv() returned: %d\n", result);
        goto DISCONNECT;
    }
    // the HTTP response code
    printf("recv %d [%.*s]\n", rcount, strstr(buffer, "\r\n")-buffer, buffer);

    // The api.ipify.org service also gives us the device's external IP address
    p = strstr(buffer, "\r\n\r\n")+4;
    printf("External IP address: %.*s\n", rcount-(p-buffer), p);
    delete[] buffer;

DISCONNECT:
    // Close the socket to return its memory and bring down the network interface
    socket.close();

    ThisThread::sleep_for(SAMPLE_TIME);
    // Bring down the ethernet interface
    net->disconnect();
    thread->terminate();
    printf("Done\n");
}
