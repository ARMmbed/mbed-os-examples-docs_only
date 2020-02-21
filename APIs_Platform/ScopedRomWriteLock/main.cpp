#include "mbed.h"

int main()
{
    // Enable execution from RAM while in main
    ScopedRomWriteLock make_rom_writable;

    //custom_flash_programming();
}
