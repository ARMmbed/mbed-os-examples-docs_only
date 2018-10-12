# IdleLoop example #

Idle Loop usage example for mbed OS

This is an example showing the purpose of Idle Loop thread that is scheduled when no other threads are ready to run. In this example, we have a regular thread that is scheduled to run every
5 seconds, and meanwhile, since no other thread is scheduled to run, the idle loop runs and toggles the LED.