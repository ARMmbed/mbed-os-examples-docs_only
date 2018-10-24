#include "mbed.h"
#include "UDPSocket.h"
#include "OnboardCellularInterface.h"

// SIM pin code goes here
#define PIN_CODE    "1234"

// Network credentials like APN go here, e.g.,
// "apn, username, password"
#define CREDENTIALS "internet"

// Number of retries /
#define RETRY_COUNT 3

// Cellular network interface object
OnboardCellularInterface iface;

// Echo server hostname
const char *host_name = "echo.u-blox.com";

// Echo server TCP port
const int port = 7;

/**
 * Connects to the Cellular Network
 */
nsapi_error_t do_connect()
{
    nsapi_error_t retcode;
    uint8_t retry_counter = 0;

    while (!iface.is_connected()) {
        retcode = iface.connect();
        if (retcode == NSAPI_ERROR_AUTH_FAILURE) {
            printf("\n\nAuthentication Failure. Exiting application\n");
            break;
        } else if (retcode == NSAPI_ERROR_OK) {
            printf("\n\nConnection Established.\n");
            break;
        } else if (retry_counter > RETRY_COUNT) {
            printf("\n\nFatal connection failure: %d\n", retcode);
            break;
        }

        printf("\n\nCouldn't connect: %d, will retry\n", retcode);
        retry_counter++;
    }

    return retcode;
}

/**
 * Opens a TCP socket with the given echo server and undergoes an echo
 * transaction.
 */
int test_send_recv()
{
    nsapi_size_or_error_t retcode;

    TCPSocket sock;

    // Prepare the connection
    retcode = sock.open(&iface);
    if (retcode != NSAPI_ERROR_OK) {
        printf("TCPSocket.open() fails, code: %d\n", retcode);
        return -1;
    }

    SocketAddress sock_addr;
    retcode = iface.gethostbyname(host_name, &sock_addr);
    if (retcode != NSAPI_ERROR_OK) {
        printf("Couldn't resolve remote host: %s, code: %d\n", host_name,
               retcode);
        return -1;
    }

    sock_addr.set_port(port);

    sock.set_timeout(15000);
    int n = 0;
    char *echo_string = "TEST";
    char recv_buf[4];

    // Connect
    retcode = sock.connect(sock_addr);
    if (retcode < 0) {
        printf("TCPSocket.connect() fails, code: %d\n", retcode);
        return -1;
    } else {
        printf("TCP: connected with %s server\n", host_name);
    }

    // Send some data
    retcode = sock.send((void*) echo_string, sizeof(echo_string));
    if (retcode < 0) {
        printf("TCPSocket.send() fails, code: %d\n", retcode);
        return -1;
    } else {
        printf("TCP: Sent %d Bytes to %s\n", retcode, host_name);
    }

    // Wait for the echo
    n = sock.recv((void*) recv_buf, sizeof(recv_buf));

    // Disconnect
    sock.close();

    if (n > 0) {
        printf("Received from echo server %d Bytes\n", n);
        return 0;
    }

    return -1;
}

int main()
{
    iface.modem_debug_on(MBED_CONF_APP_MODEM_TRACE);

    /* Set Pin code for SIM card */
    iface.set_sim_pin(PIN_CODE);

    /* Set network credentials here, for example the APN */
    iface.set_credentials(CREDENTIALS);

    printf("\n\nmbed-os-example-cellular, Connecting...\n");

    /* Attempt to connect to a cellular network */
    if (do_connect() == NSAPI_ERROR_OK) {
        int ret = test_send_recv();
        if (ret == 0) {
            printf("\n\nSuccess. Exiting \n\n");
            return 0;
        }
    }

    printf("\n\nFailure. Exiting \n\n");
    return -1;
}
