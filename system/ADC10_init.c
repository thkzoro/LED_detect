#include <msp430.h>

/*
 *  ======== ADC10_init ========
 *  Initialize MSP430 10-bit Analog to Digital Converter
 */
void ADC10_init(void)
{
    /* 
     * Control Register 0
     * 
     * ~ADC10SC -- No conversion
     * ~ENC -- Disable ADC
     * ~ADC10IFG -- Clear ADC interrupt flag
     * ADC10IE -- Enable ADC interrupt
     * ~ADC10ON -- Switch Off ADC10
     * REFON -- Enable ADC reference generator
     * REF2_5V -- Set reference voltage generator = 2.5V
     * ~MSC -- Disable multiple sample and conversion
     * ~REFBURST -- Reference buffer on continuously
     * ~REFOUT -- Reference output off
     * ~ADC10SR -- Reference buffer supports up to ~200 ksps
     * ADC10SHT_2 -- 16 x ADC10CLKs
     * SREF_1 -- VR+ = VREF+ and VR- = VSS
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    ADC10CTL0 = ADC10IE | ADC10ON | REFON | REF2_5V | ADC10SHT_2 | SREF_1;

    /* Analog (Input) Enable Control Register 0 */
    ADC10AE0 = BIT0;


    /* Software delay for REFON to settle */
    __delay_cycles(30000);
    ADC10CTL0 |= ENC;
}
