# I2C example

This example shows how to use `I2C` API to read temperature sensor. The Mbed OS `I2C` API uses 8 bit addressing and will auto append the 0 or 1 for read/write mode. Please keep in mind that every I2C set up has its own quirks so this example may not work out of the box for your sensor / application. Make sure to check the data sheet for your part for the timing / register access specification.
