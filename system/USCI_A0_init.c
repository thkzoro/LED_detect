#include <msp430.h>

/* USER CODE START (section: USCI_A0_init_c_prologue) */
/* User defined includes, defines, global variables and functions */
/* USER CODE END (section: USCI_A0_init_c_prologue) */

/*
 *  ======== USCI_A0_init ========
 *  Initialize Universal Serial Communication Interface A0 UART 2xx
 */
void USCI_A0_init(void)
{
    /* Disable USCI */
    UCA0CTL1 |= UCSWRST;

    /* 
     * Control Register 1
     * 
     * UCSSEL_2 -- SMCLK
     * ~UCRXEIE -- Erroneous characters rejected and UCAxRXIFG is not set
     * ~UCBRKIE -- Received break characters do not set UCAxRXIFG
     * ~UCDORM -- Not dormant. All received characters will set UCAxRXIFG
     * ~UCTXADDR -- Next frame transmitted is data
     * ~UCTXBRK -- Next frame transmitted is not a break
     * UCSWRST -- Enabled. USCI logic held in reset state
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCA0CTL1 = UCSSEL_2 | UCSWRST;
    
    /* 
     * Modulation Control Register
     * 
     * UCBRF_0 -- First stage 0
     * UCBRS_7 -- Second stage 7
     * ~UCOS16 -- Disabled
     * 
     * Note: ~UCOS16 indicates that UCOS16 has value zero
     */
    UCA0MCTL = UCBRF_0 | UCBRS_7;
    
    /* Baud rate control register 0 */
    UCA0BR0 = 138;
    
    /* Enable USCI */
    UCA0CTL1 &= ~UCSWRST;
    
    /* USER CODE START (section: USCI_A0_init_epilogue) */
    IFG2 &= ~(UCA0TXIFG | UCA0RXIFG);
    IE2 |= UCA0TXIE | UCA0RXIE;
//    IE2 |= UCA0TXIE;
    /* USER CODE END (section: USCI_A0_init_epilogue) */
}
