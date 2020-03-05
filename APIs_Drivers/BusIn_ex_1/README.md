# BusIn example

This example shows how to use the 
BusIn is an abstraction that takes any pins and makes them appear as though they are linearly memory mapped for ease of use. This abstraction is useful for checking multiple inputs in a single pass. In general this abstraction can be used to make code less cluttered, clearer, and take less time to write.  

**Note**: Please pay attention to the ordering of pins in the initialization. The order pins are initialized in the reverse order that bits are OR'd together.
