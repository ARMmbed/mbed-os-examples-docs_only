#include "mbed.h"
#include "MK64F12.h"

void bm_gpio_init(void)
{
    SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;
    PORTB->PCR[22] = PORT_PCR_MUX(1U);
    PTB->PDDR = (1U << 22U);
}

void bm_delay(void)
{
    volatile unsigned int i, j;

    for (i = 0U; i < 100000U; i++) {
        for (j = 0U; j < 100U; j++) {
            __asm__("nop");
        }
    }
}

int main(void)
{
    bm_gpio_init();

    PTB->PSOR = (1U << 22U);

    while (1) {
        PTB->PTOR = (1U << 22U);
        bm_delay();
    }
}

