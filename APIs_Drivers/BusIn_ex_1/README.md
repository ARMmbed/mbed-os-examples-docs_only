# BusIn example

BusIn is an abstraction that takes any pins and makes them appear as though they are linearly memory mapped for ease of use. This abstraction is useful for checking multiple inputs at once. In general, you can use this abstraction to make code less cluttered, clearer and quicker to write.  

**Note**: Please pay attention to the ordering of pins in the initialization. The order pins are initialized in the reverse order that bits are OR'd together.
