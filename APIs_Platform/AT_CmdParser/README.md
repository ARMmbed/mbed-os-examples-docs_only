## ATCmdParser Example ##

This is a example showing ATCmdParser usage with ESP8266 WiFi module.

The program retrieves the FW version of the ESP8266 module connected over UART using AT commands. 

##  Getting started

1. Import the example
2. Compile and generate binary   
5. Open a serial console session with the target platform using the following parameters:
    * **Baud rate:** 9600
    * **Data bits:** 8
    * **Stop bits:** 1
    * **Parity:** None
 6. Flash the target with the compiled binary. 
 7. The serial console should display a similar output to below, indicating a successful AT communication:
 ```
ATCmdParser with ESP8266 example
AT> AT+GMR
AT? SDK version:%*d%n
AT< AT+GMR
AT<
AT< AT version:1.3.0.0(Jul 14 2016 18:54:01)
AT= SDK version:2
AT? OK%n
AT< .0.0(656edbf)
AT< compile time:Jul 19 2016 18:44:44
AT= OK
ATCmdParser: Retrieving FW version
ATCmdParser: FW version: 2
ATCmdParser: Retrieving FW version success
Done

```

