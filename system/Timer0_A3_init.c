#include <msp430.h>
extern void TA0_GPIO_init(void);
/* USER CODE START (section: Timer0_A3_init_c_prologue) */
/* User defined includes, defines, global variables and functions */
/* USER CODE END (section: Timer0_A3_init_c_prologue) */

/*
 *  ======== Timer0_A3_init ========
 *  Initialize MSP430 Timer0_A3 timer
 */
void Timer0_A3_init(void)
{
    TA0_GPIO_init();
    /* 
     * TA0CCTL2, Capture/Compare Control Register 2
     * 
     * CM_0 -- No Capture
     * CCIS_0 -- CCIxA
     * ~SCS -- Asynchronous Capture
     * ~SCCI -- Latched capture signal (read)
     * ~CAP -- Compare mode
     * OUTMOD_4 -- PWM output mode: 4 - Toggle
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     *
     */
    TA0CCR0 = 1000; //设置频率1K
    /*输出引脚P3.5,驱动信号，驱动LED*/
    TA0CCTL1 = CM_0 | CCIS_0 | OUTMOD_4;
    /*输出引脚P3.6,参考信号，用于相敏检波*/
    TA0CCTL2 = CM_0 | CCIS_0 | OUTMOD_0 | OUT;
    /* 
     * TA0CTL, Timer_A3 Control Register
     * 
     * TASSEL_2 -- SMCLK
     * ID_0 -- Divider - /1
     * MC_1 -- Up Mode
     */
    TA0CTL = TASSEL_2 | ID_3 | MC_1 | TACLR;
}
