# Time example

You can use the time interface to access the Real Time Clock (RTC). The time is set as an offset measured in seconds from the time epoch, which is library specific. The accepted time epoch is the [Unix Epoch](https://en.wikipedia.org/wiki/Unix_time).

**Tip:** An online converter between human readable time and Unix Epoch time is useful, such as the [EpochConverter](https://www.epochconverter.com/).</span>

If the system is not battery powered, the RTC time resets at each power on, or cold reset. Make sure to either provide battery power to keep the time or to set it each time the device starts. During software or warm reset (for example, watchdog reset) RTC counts without interrupt.

There is no official time API. Instead, use the functions in the example code.

