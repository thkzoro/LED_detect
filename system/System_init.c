#include <msp430.h>


/*
 *  ======== System_init ========
 *  Initialize MSP430 Status Register
 */
void System_init(void)
{
    do
    {
        IFG1 &= ~OFIFG;
        __delay_cycles(800);
    } while (IFG1 & OFIFG);


}
