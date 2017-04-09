#include <msp430G2553.h>
#include <UART.h>
#include <SPI.h>
#include <global.h>
#include <handle.h>
#include <oled.h>

extern void BCS_init(void);
extern void UART_init(void);
extern void ADC10_init(void);

extern void Timer0_A3_init(void);
extern void Timer1_A3_init(void);



int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCS_init();
    UART_init();
    SPI_init();
    ADC10_init();
    Timer0_A3_init();
    Timer1_A3_init();
    _enable_interrupts();
    UART_Tx_string("The LED light source intensity distribution measurement system\n");
    OLED_Init();
    OLED_ShowString(0, 0, "LED detect");
    LPM0;
	while(1)
	{
	    switch (run_status) {
	    	case RX_complete:
	    	    RX_complete_handle();
	    	    run_status=other;
	    	    break;

           case sample_end:
               sample_end_handle();
               run_status=other;
               break;
           case steer_turn_end:
               TA1_work_mode_switch(TA1_capture_mode);
               run_status=other;
               break;
           case capture_finish:
//               if(xt_min_freq && xt_max_freq)
//               {
                   TA1_work_mode_switch(TA1_AD_mode);
//               }
               run_status=other;
               break;

           case sleep:
               OLED_Clear();
               OLED_ShowString(0, 0, "test complete");
               LPM0;
               break;

           case other:LPM0;
               break;

           default:
               break;
       }
   }
 }
