# EventFlags example

EventFlags usage example for Mbed OS.

This is an example showing a basic usage of `EventFlags` class. One thread is
waiting for either of the two defined flags to be set. The second thread is
periodically setting the flags.

Note that the `wait_any()` method is also used to clear the flags.
