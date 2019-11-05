# EventFlags example for Mbed OS

This example shows the `EventFlags` class. One thread is waiting for either of the two defined flags to be set. The second thread is
periodically setting the flags.

Note that you can use the `wait_any()` method to clear the flags.

Note: For more context or to see this example in a rendered form, you can import into the Arm Mbed Online Compiler, please see [the documentation](https://os.mbed.com/docs/mbed-os/latest/apis/eventflags.html).
