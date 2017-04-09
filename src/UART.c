#include "MSP430G2553.h"
#include <global.h>
#include <UART.h>

extern void UART_GPIO_init(void);

static int UART_Tx_Complete_flag=1;


int get_UART_Tx_state(void){
	return UART_Tx_Complete_flag;
}

void UART_Tx_string(unsigned char *Ptr){
    static unsigned int i=0;
    	if (tx_f[i].empty==0) {
        tx_f[i].UART_Tx_FIFO=Ptr;
        tx_f[i].empty=1;
        if(UART_Tx_Complete_flag==1)
        {
            IFG2 |= UCA0TXIFG;
        }
        UART_Tx_Complete_flag=0;
        i++;
        if(i>=UART_Tx_FIFO_size) i=0;
    }

}


inline void UART_Tx_IRQHandler(void){
    static unsigned int i=0;
       
        if (tx_f[i].empty)
       {
           if(*tx_f[i].UART_Tx_FIFO)
           {
               UCA0TXBUF = *tx_f[i].UART_Tx_FIFO++;
           }
           else
           {
               tx_f[i].empty=0;
               i++;
               if(i>=UART_Tx_FIFO_size)i=0;
           }
       }
       else
       {
           UART_Tx_Complete_flag=1;
           IFG2 &= ~ UCA0TXIFG;
       }
	
}

inline char UART_Rx_IRQHandler(void){
    static unsigned int i=0;
    UART_Rx_FIFO[i]=UCA0RXBUF;
    if( UART_Rx_FIFO[i]=='\n')
    {
        UART_Rx_FIFO[i+1]='\0';
        i=0;
       return 1;
    }
    else
    {
        i++;
        if(i>=UART_Rx_FIFO_size)
        {
            i=0;
        }
        return 0;
    }
}

void UART_init(void){
    UART_GPIO_init();
    USCI_A0_init();
}
