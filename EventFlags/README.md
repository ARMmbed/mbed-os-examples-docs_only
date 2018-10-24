# EventFlags example

EventFlags usage example for Mbed OS.

This is an example showing the `EventFlags` class. One thread is
waiting for either of the two defined flags to be set. The second thread is
periodically setting the flags.

Note that you can use the `wait_any()` method to clear the flags.
