## USBCDC_ECM example

The example sends an Ethernet frame that carries "Hello world" payload with a custom EtherType to the host PC. You can capture the frame by using a program called "Wireshark":

1. Flash the board, and ensure the target's USB is plugged into the PC.
2. Use `dmesg -w` linux command to determine address of the USB CDC Ethernet device.
3. Use `ifconfig` linux command to determine interface related to the the USB CDC Ethernet device.
4. Open Wireshark.
5. Click **Capture > Options** to select the correct capture interface.
6. Click **Capture > Start**.
7. Click captured packet from source address 12:34:56:78:9a:bc to see the "Hello world" payload.

**Note:** Because Windows doesn't provide native support for the USB CDC-ECM model, you must use third party drivers to use this class on Windows. It is suggested to run this example on Linux.
