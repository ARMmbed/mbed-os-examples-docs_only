## Baremetal Blinky example using Mbed OS

This guide reviews the steps required to build and run a baremetal Blinky application on FRDM-K64F without using DigitalOut class and timers.

Please install [Mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).

### Import the example application

From the command-line, import the example:

```
git clone https://github.com/ARMmbed/mbed-os-examples-docs_only.git
cd mbed-os-examples-docs_only/Baremetal-Blinky
mbed config root .
mbed deploy
```

#### Now compile


```
mbed compile -m k64f -t gcc_arm 
```

#### Program your board

1. Connect your Mbed device to the computer over USB.
2. Copy the binary file to the Mbed device.
3. Observe LED blinking.

