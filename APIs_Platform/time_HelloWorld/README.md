# Time example

The time interface is used to access the Real Time Clock (RTC). The time is set as an offset measured in seconds from the time epoch, which is library specific. In general the accepted time epoch is the [Unix Epoch](https://en.wikipedia.org/wiki/Unix_time). An online converter between human readable time and Unix Epoch time is handy, try [this](https://www.epochconverter.com/) one. If the system is not battery powered then on each power-on (cold reset) the rtc time will be reset. Make sure to either provide battery power to keep the time or to set it each time the device is started. During software or warm reset (e.g watchdog reset) RTC counts without interrupt.

There is no official time API, instead you use the functions in the example code.

