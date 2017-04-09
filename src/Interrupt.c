#include <msp430.h>
#include <global.h>
#include <handle.h>

extern void UART_Tx_IRQHandler(void);
extern char UART_Rx_IRQHandler(void);
extern void SPI_Tx_IRQHandler(void);
extern void SPI_Rx_IRQHandler(void);

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR_HOOK(void)
{
    if (IFG2 & UCA0TXIFG)
    {
        UART_Tx_IRQHandler();
    }

    else if (IFG2 & UCB0TXIFG)
    {
        SPI_Tx_IRQHandler();
        LPM0_EXIT;
    }
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void)
{

    if (IFG2 & UCA0RXIFG)
    {
        if(UART_Rx_IRQHandler()==1){
            run_status=RX_complete;
            LPM0_EXIT;
        }

    }

    else if (IFG2 & UCB0RXIFG)
    {

    }
}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR_HOOK(void)
{
    /* USER CODE START (section: ADC10_ISR_HOOK) */
    static unsigned int i=0;
    AD_value[i]=ADC10MEM;
    i++;
    if(i>=AD_sample_time)
    {
        i=0;
        run_status=sample_end;
        LPM0_EXIT;
    }
    /* USER CODE END (section: ADC10_ISR_HOOK) */
}
/*
 *  ======== Timer1_A3 Interrupt Service Routine ========
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void)
{
    /* USER CODE START (section: TIMER1_A0_ISR_HOOK) */
    static int AD_count=0;
   
    TA1CCTL0 &= ~CCIFG;
    ADC10CTL0 |= ADC10SC; //开始采样信号
    AD_count++;
    if(AD_count>=AD_sample_time)
    {
        /*关闭中断*/
        TA1CCTL0 &= ~CCIE;
        AD_count=0;
    }
    /* USER CODE END (section: TIMER1_A0_ISR_HOOK) */
}

/*
 *  ======== Timer1_A3 Interrupt Service Routine ======== 
 */

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR_HOOK(void)
{
    /* USER CODE START (section: TIMER1_A1_ISR_HOOK) */
    static int first=0;

    switch (__even_in_range(TA1IV, TA1IV_TAIFG))    // Efficient switch-implementation
            {
                case TA1IV_TACCR1:  TA1CCTL1 &= ~CCIFG;
                    steer_delay_time--;

                    if(steer_delay_time==0)
                    {
                        TA1CCTL1 &= ~(OUTMOD_7 | CCIE);
                        run_status=steer_turn_end;
                        LPM0_EXIT;
                        if(steer_position>=20)
                        {
                            run_status=sleep;
                        }
                    }
                    break;

                case TA1IV_TACCR2:
                    first++;
                    if(first==1){
                        /*1.TA1R清0，0为第一个上升沿的时间*/
                        TA1R = 0;
                        /*2.捕获到上升沿，马上输出PWM r(t)，PWM输出模式设置为触发模式*/
                        TA0CCR2 = TA0R; //保持相位相等
                        TA0CCTL2 &=  ~OUTMOD_7;//复位
                        TA0CCTL2 |=  OUTMOD_4;//
                        /*3.打开定时器溢出中断*/
                        TA1CTL |= TAIE;
                        capture_overflow=0;
                        TA1CTL &= ~TAIFG; //清捕定时器溢出中断志位
                    }
                    else
                    {
                        capture_value=TA1CCR2;
                        first=0;
                        /*关闭定时器捕获、溢出中断*/
                        TA1CCTL2 &= ~CCIE;
                        TA1CTL &= ~TAIE;
                        run_status=capture_finish;
                        LPM0_EXIT;
                    }
                    /*清捕获标志位*/
                    TA1CCTL2 &= ~CCIFG;
                    break;

                case TA1IV_TAIFG:
                    TA1CTL &= ~TAIFG; //清捕定时器溢出中断志位
                    capture_overflow++;
                    break;

                default:
                    break;
            }

    /* USER CODE END (section: TIMER1_A1_ISR_HOOK) */
}

/*
 *  ======== Watchdog Timer Interval Interrupt Handler Generation ========
 */
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR_HOOK(void)
{
    /* USER CODE START (section: WDT_ISR_HOOK) */
    /* replace this comment with your code */
    /* USER CODE END (section: WDT_ISR_HOOK) */
}
