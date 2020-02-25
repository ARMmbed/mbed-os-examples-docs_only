# Shared event example

Instead of creating a special thread, you can use a shared event queue, which shares the queue with other system components, saving RAM. Because the event queue is shared, you should limit the execution time of your event functions to avoid delaying other users’ events excessively. 
