#include <msp430.h>

/* USER CODE START (section: USCI_B0_init_c_prologue) */
/* User defined includes, defines, global variables and functions */
/* USER CODE END (section: USCI_B0_init_c_prologue) */
    
/*
 *  ======== USCI_B0_init ========
 *  Initialize Universal Serial Communication Interface B0 SPI 2xx
 */
void USCI_B0_init(void)
{
    /* Disable USCI */
    UCB0CTL1 |= UCSWRST;
    
    /* 
     * Control Register 0
     * 
     * ~UCCKPH -- Data is changed on the first UCLK edge and captured on the following edge
     * ~UCCKPL -- Inactive state is low
     * ~UCMSB -- LSB first
     * ~UC7BIT -- 8-bit
     * UCMST -- Master mode
     * UCMODE_0 -- 3-Pin SPI
     * UCSYNC -- Synchronous Mode
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCB0CTL0 = UCCKPL | UCMSB | UCMST | UCMODE_0 | UCSYNC;
    /* 
     * Control Register 1
     * 
     * UCSSEL_2 -- SMCLK
     * UCSWRST -- Enabled. USCI logic held in reset state
     */
    UCB0CTL1 = UCSSEL_2 | UCSWRST;
    
    /* Bit Rate Control Register 0 */
    UCB0BR0 = 16;
    
    /* Enable USCI */
    UCB0CTL1 &= ~UCSWRST;
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);
   //    IE2 |= UCB0TXIE | UCB0RXIE;
       IE2 |= UCB0TXIE;
    

}
