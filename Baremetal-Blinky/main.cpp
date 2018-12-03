#include "mbed.h"

// Port A0: 0x40004000 GPIO0 to GPIO7
// Port A1: 0x40005000 GPIO8 to GPIO15 Use GPIO13 (SW2) as input, GPIO9(D10 Red) as output
// Port A2: 0x40006000 GPIO16 to GPIO23
// Port A3: 0x40007000 GPIO24 to GPIO31

#define WAIT_CYCLES_LONG          10000000
#define WAIT_CYCLES_SHORT         1000000
#define INPUT_PIN_PORTA1          5
#define OUTPUT_PIN_PORTA1         1
#define GPIO_PORTA1_ADDRESS       0x40005000
#define GPIO_PAD_CONFIG_9_ADDRESS 0x4402E0C4
#define OFFSET_DIR                0x400
#define OFFSET_DATA               0
#define ARCM_BASE                 0x44025000
#define PRCM_RUN_MODE_CLK         0x00000001
#define PRCM_SLP_MODE_CLK         0x00000100
#define GPIO_PAD_CONFIG_9         0x4402E0C4
#define PAD_MODE_MASK             0x0000000F

static void set_gpio_dir()
{
    // Configure direction Bit 7:0 DIR, 0 = input, 1 = output
    *((volatile unsigned long*)(GPIO_PORTA1_ADDRESS + OFFSET_DIR)) &= ~0x20; // Configure SW2 as input
    *((volatile unsigned long*)(GPIO_PORTA1_ADDRESS + OFFSET_DIR)) |= 0x2;   // Configure D10 as output

}

static const unsigned long g_ulPinToPadMap[64] =
{
    10,11,12,13,14,15,16,17,255,255,18,
    19,20,21,22,23,24,40,28,29,25,255,
    255,255,255,255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,255,255,255,
    31,255,255,255,255,0,255,32,30,255,1,
    255,2,3,4,5,6,7,8,9
};

void PinModeSet(unsigned long ulPin,unsigned long ulPinMode)
{
    unsigned long ulPad;

    // Get the corresponding Pad
    ulPad = g_ulPinToPadMap[ulPin & 0x3F];

    // Calculate the register address
    ulPad = ((ulPad << 2) + (0x4402E000+0x000000A0));

    // Set the mode.
    *((volatile unsigned long*)(ulPad)) = (((*((volatile unsigned long*)(ulPad))) & ~PAD_MODE_MASK) |  ulPinMode) & ~(3<<10);
}

int main()
{
    PinModeSet(0x0000003F,0x000000000);
    *((volatile unsigned long*)(ARCM_BASE + 0x58)) |= PRCM_RUN_MODE_CLK || PRCM_SLP_MODE_CLK;

    unsigned long wait_cycles_in_use = WAIT_CYCLES_SHORT;
    volatile unsigned long delay = 0;

    set_gpio_dir();
    *((volatile unsigned long*)(GPIO_PAD_CONFIG_9))|= 0x220;

    while (true)
    {

        // Check if SW2 is pressed
        if (*(volatile unsigned long *)(GPIO_PORTA1_ADDRESS + OFFSET_DATA + ((1 << INPUT_PIN_PORTA1) << 2)))
        {
            wait_cycles_in_use = WAIT_CYCLES_LONG;
        }

        *(volatile unsigned long *)(GPIO_PORTA1_ADDRESS + OFFSET_DATA + ((1 << OUTPUT_PIN_PORTA1) << 2)) = (OUTPUT_PIN_PORTA1 << 1);
        delay = wait_cycles_in_use;
        while (delay--);
        *(volatile unsigned long *)(GPIO_PORTA1_ADDRESS + OFFSET_DATA + ((1 << OUTPUT_PIN_PORTA1) << 2)) = 0;
        delay = wait_cycles_in_use;
        while (delay--);
    }
}

