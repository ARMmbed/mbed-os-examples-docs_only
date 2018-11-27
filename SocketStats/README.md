# Getting started with network socket statistics on Mbed OS

This example demonstrates how you can collect statistics from network sockets. You can enable statistics with the `nsapi.socket-stats-enable` configuration option:

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

Invoke `mbed compile`, and specify the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the Arm Compiler 5:

```
mbed compile -t <toolchain> -m <target>
```

Example: `mbed compile -m K64F -t ARM`

### Documentation

You can find more information on the network socket API in the [Mbed OS 5 documentation](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/communication/network_sockets/).

You can also find more information on the socket statistic API in the [Mbed OS 5 documentation](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/).

 
### Note

The current example is limited to the ethernet interface on supported devices. To use the example with a different interface, please follow the [socket example readme](https://github.com/ARMmbed/mbed-os-example-sockets/blob/master/README.md).
