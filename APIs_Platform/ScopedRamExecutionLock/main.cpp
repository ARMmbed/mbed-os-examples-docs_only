#include "mbed.h"

int main()
{
    // Enable execution from RAM while in main
    ScopedRamExecutionLock make_ram_executable;

    //some_function_in_ram();
}
