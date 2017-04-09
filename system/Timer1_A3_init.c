#include <msp430.h>

extern void TA1_GPIO_init(void);

/*
 *  ======== Timer1_A3_init ========
 *  Initialize MSP430 Timer1_A3 timer
 */
void Timer1_A3_init(void)
{
    TA1_GPIO_init();
    TA1CCTL0 = CM_0 | CCIS_0 | OUTMOD_0;
    /*用于舵机驱动*/
    TA1CCTL1 = CM_0 | CCIS_0 | OUTMOD_0;
    /*P2.4，捕获*/
    TA1CCTL2 = CM_1 | CCIS_0 | SCS | CAP | OUTMOD_0;
    TA1CTL = TASSEL_2 | ID_0 | MC_0 | TACLR;
}
