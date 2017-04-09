#include <msp430.h>

void BCS_init(void)
{
    BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;

    if (CALBC1_16MHZ != 0xFF) {
        __delay_cycles(10000);
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
        DCOCTL = CALDCO_16MHZ;
    }
    BCSCTL1 |= XT2OFF | DIVA_0;

    BCSCTL3 = XT2S_0 | LFXT1S_2 | XCAP_1;

}
