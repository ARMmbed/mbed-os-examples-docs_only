#include "mbed.h"
#include "FlashIAPBlockDevice.h"

// Create flash IAP block device
FlashIAPBlockDevice bd;

int main() {
    printf("FlashIAPBlockDevice test\n");

    // Initialize the flash IAP block device and print the memory layout
    bd.init();
    printf("Flash block device size: %llu\n",         bd.size());
    printf("Flash block device read size: %llu\n",    bd.get_read_size());
    printf("Flash block device program size: %llu\n", bd.get_program_size());
    printf("Flash block device erase size: %llu\n",   bd.get_erase_size());

    // Write "Hello World!" to the first block
    char *buffer = (char*)malloc(bd.get_erase_size());
    sprintf(buffer, "Hello World!\n");
    bd.erase(0, bd.get_erase_size());
    bd.program(buffer, 0, bd.get_erase_size());

    // Read back what was stored
    bd.read(buffer, 0, bd.get_erase_size());
    printf("%s", buffer);

    // Deinitialize the device
    bd.deinit();
}
