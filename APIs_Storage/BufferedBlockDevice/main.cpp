#include "BufferedBlockDevice.h"
#include "HeapBlockDevice.h"
#include <cstdio>

int main()
{
    // Define a HeapBlockDevice with program size 512 bytes and read size 256
    HeapBlockDevice heap_bd(1024, 256, 512, 512);
    // BufferedBlockDevice is used to program or read a much smaller amount of data than the minimum program or read size supported by the underlying block device
    BufferedBlockDevice buf_bd(&heap_bd);

    // This initializes the buffered block device (as well as the underlying heap block device)
    int err = buf_bd.init();

    uint8_t buf[8];
    for (uint8_t i = 0; i < sizeof(buf); i++) {
        buf[i] = i;
    }

    // Now we can program an 8-byte buffer (we couldn't do that in the underlying block device, which had a 512-byte program size)
    err = buf_bd.program(buf, 0, sizeof(buf));


    // Now read any amount of data from any address (for example, the last three bytes of data from address 5)
    memset(buf, 0, 8);
    err = buf_bd.read(buf, 5, 3);

    printf("Read Data (Expected 5,6,7): %d %d %d\n", (int)(buf[0]), (int)(buf[1]), (int)(buf[2]));

    // Ensure programmed data is flushed to the underlying block device
    err = buf_bd.sync();

    // Finally, deinint the BufferedBlockDevice (which also deinits its underlying block device)
    err = buf_bd.deinit();
}
