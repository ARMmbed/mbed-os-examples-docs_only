# Getting started with Network Socket Statistics on Mbed OS

This example demonstrates how you can collect statistics from network sockets. Statistics are enabled by `nsapi.socket-stats-enable` config option.

```
{
    "target_overrides": {
        "*": {
            "nsapi.socket-stats-enable": true
        }
    }
}
```

### Building

Invoke `mbed compile`, and specify the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the ARM Compiler 5:

```
mbed compile -t <toolchain> -m <target>
```
Example: `mbed compile -m K64F -t ARM`

### Documentation
More information on the network-socket API can be found in the [mbed handbook](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/communication/network_sockets/).

More information on the socket statistic API can be found in the [mbed handbook](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/).

 
### Note
The current example is limited to the ethernet interface on supported devices. To use the example with a different interface, please follow the [socket example readme] (https://github.com/ARMmbed/mbed-os-example-sockets/blob/master/README.md).