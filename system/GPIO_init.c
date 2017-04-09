#include <msp430.h>
/*
 *  ======== GPIO_init ========
 *  Initialize MSP430 General Purpose Input Output Ports
 *
 *  The GPIO registers should be set in a specific order:
 *     PxOUT
 *     PxSEL or PxSELx
 *     PxDIR
 *     PxREN
 *     PxIES
 *     PxIFG
 *     PxIE
 *
 *     This will ensure that:
 *         - IFG doesn't get set by manipulating the pin function, edge
 *           select, and pull-up/down resistor functionalities (see
 *           Section 8.2.6 of the MSP430 User's manual)
 *         - Glitch-free setup (configuring the OUT register _before_
 *           setting the pin direction)
 *         - Pull-up/pull-down resistor enable with the correct direction
 *           (.up. vs. .down.)
 */
void TA0_GPIO_init(void){
    /* TA0，PWM管脚配置
     * p3.5->TA0.1
     * p3.6->TA0.2
     * P3SEL 管脚选择，
     * 设置为输出 */
    P3SEL |= BIT5 | BIT6;
    P3DIR |= BIT5 | BIT6;
}

void TA1_GPIO_init(void){
    /* TA1，管脚配置
     * p3.2->TA1CCR1
     * p2.4->TA1CCR2
     * P3SEL 管脚选择，
     * 设置为输出 */
    P3SEL |= BIT2;
    P3DIR |= BIT2;

    P2SEL |= BIT4;
    P2DIR &= ~BIT4;
}

void UART_GPIO_init(void){
    /*UART，管脚配置
     *p1.1->RXD
     *p1.2->TXD
     * */
    P1SEL  |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
}
void SPI_GPIO_init(void){
    /*SPI，管脚配置
     *p1.4->STE
     *p1.5->CLK
     *p1.6->SOMI//oled不用
     *p1.7->SIMO
     */

//    P1SEL  |= BIT4 | BIT5 | BIT6 | BIT7;
//    P1SEL2 |= BIT4 | BIT5 | BIT6 | BIT7;
//    P1DIR  |= BIT4 | BIT5 | BIT6 | BIT7;
        P1SEL  |=  BIT5 | BIT6 | BIT7;
        P1SEL2 |=  BIT5 | BIT6 | BIT7;
        P1DIR  |= BIT4 | BIT5 | BIT6 | BIT7;
//        P1OUT  |= BIT4;
        P1OUT  &= ~BIT4;
}
