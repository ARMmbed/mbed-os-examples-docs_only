#if !DEVICE_QSPI
#error [NOT_SUPPORTED] QSPI not supported for this target
#endif

#include "mbed.h"
#include "drivers/QSPI.h"

#define CMD_WRITE 0x02
#define CMD_READ  0x03
#define ADDRESS   0x1000
#define BUF_SIZE  10

// hardware ssel (where applicable)
QSPI qspi_device(QSPI_FLASH1_IO0, QSPI_FLASH1_IO1, QSPI_FLASH1_IO2, QSPI_FLASH1_IO3, QSPI_FLASH1_SCK, QSPI_FLASH1_CSN); // io0, io1, io2, io3, sclk, ssel

int main() {
    char tx_buf[] = { 'h', 'e', 'l', 'l', 'o', '\n' };
    char rx_buf[BUF_SIZE];
    size_t buf_len = sizeof(tx_buf);
     qspi_status_t result;

    result = qspi_device.configure_format(QSPI_CFG_BUS_SINGLE, QSPI_CFG_BUS_SINGLE,
                                        QSPI_CFG_ADDR_SIZE_24, QSPI_CFG_BUS_SINGLE,
                                        QSPI_CFG_ALT_SIZE_8, QSPI_CFG_BUS_SINGLE, 0);
    if (result != QSPI_STATUS_OK) {
        printf("Config format failed\n");
    }

    qspi_device.set_frequency(10000000);
    result = qspi_device.write(CMD_WRITE, 0, ADDRESS, tx_buf, &buf_len);
    if (result != QSPI_STATUS_OK) {
        printf("Write failed\n");
        return result;
    }
    printf("Write done: %s \n", tx_buf);

    result = qspi_device.read(CMD_READ, 0, ADDRESS, rx_buf, &buf_len);
    if (result != QSPI_STATUS_OK) {
        printf("Read failed\n");
        return result;
    }
    printf ("Data Read = %s\n", rx_buf);
    return 0;
}
