# mbed-os-example-http-server

This application demonstrates how to run an HTTP server on an mbed OS 5 device.

Request parsing is done through [nodejs/http-parser](https://github.com/nodejs/http-parser).

## To build

1. Open ``mbed_app.json`` and change the `network-interface` option to your connectivity method ([more info](https://github.com/ARMmbed/easy-connect)).
2. Build the project in the online compiler or using mbed CLI.
3. Flash the project to your development board.
4. Attach a serial monitor to your board to see the debug messages.

## Tested on

* K64F with Ethernet.
* NUCLEO_F411RE with ESP8266.
    * For ESP8266, you need [this patch](https://github.com/ARMmbed/esp8266-driver/pull/41).

But every networking stack that supports the [mbed OS 5 NetworkInterface API](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/communication/network_sockets/) should work.
