# IdleLoop example #

IdleLoop usage example for Mbed OS

This is an example showing the purpose of IdleLoop thread that is scheduled when no other threads are ready to run. In this example, we have a regular thread that is scheduled to run every 5 seconds. Because no other thread is scheduled to run, IdleLoop runs and toggles the LED.
