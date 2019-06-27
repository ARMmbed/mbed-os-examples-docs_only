## USBCDC_ECM example

The example sends an Ethernet frame that carries "Hello world" payload with a custom EtherType to the host PC. You can capture the frame by using a program called "Wireshark":

1. Flash the board, and ensure the target's USB is plugged into the PC.
2. Open Wireshark.
3. Click **Capture > Options** to select the correct capture interface.
4. Click **Capture > Start**.
5. Click captured packet from source address 12:34:56:78:9a:bc to see the "Hello world" payload.

**Note:** Because Windows doesn't provide native support for the USB CDC-ECM model, you must use third party drivers to use this class on Windows.

To see this example published as part of the full documentation for USBCDC_ECM, please see the [Mbed OS documentation](https://os.mbed.com/docs/mbed-os/latest/apis/usbcdc-ecm.html).
