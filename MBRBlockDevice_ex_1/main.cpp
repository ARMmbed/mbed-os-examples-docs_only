#include "mbed.h"
#include "HeapBlockDevice.h"
#include "MBRBlockDevice.h"

int main(void) {
    // Create a block device with 64 blocks of size 512
    printf("Create a block device with 64 blocks of size 512\n");
    HeapBlockDevice mem(64*512, 512);

    // Partition into two partitions with ~half the blocks
    printf("Partition into two partitions with ~half the blocks\n");
    MBRBlockDevice::partition(&mem, 1, 0x83, 0*512, 32*512);
    MBRBlockDevice::partition(&mem, 2, 0x83, 32*512);

    // Create a block device that maps to the first 32 blocks (excluding MBR block)
    printf("Create a block device that maps to the first 32 blocks (excluding MBR block)\n");
    MBRBlockDevice part1(&mem, 1);

    // Create a block device that maps to the last 32 blocks
    printf("Create a block device that maps to the last 32 blocks\n");
    MBRBlockDevice part2(&mem, 2);
}
