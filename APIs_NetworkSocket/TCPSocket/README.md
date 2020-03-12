# TCPSocket Example
 
This is a quick example of a simple HTTP client program using the
network-socket API that is provided as a part of [mbed-os](github.com/armmbed/mbed-os).
 
The program brings up an underlying network interface, and uses it to perform an HTTP
transaction over a TCPSocket.
 
**Note:** The current example is limited to the ethernet interface on supported devices.
To use the example with a different interface, you will need to modify main.cpp and
replace the EthernetInterface class with the appropriate interface.
