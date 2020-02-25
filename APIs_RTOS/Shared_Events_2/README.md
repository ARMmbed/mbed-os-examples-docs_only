# Shared event example

Instead of creating special thread user can use shared event queue i.e. sharing it with other system components and saving RAM. As the event queue is shared, you should limit the execution time of your event functions to avoid delaying other users’ events excessively. 

