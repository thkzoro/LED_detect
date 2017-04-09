#include <msp430.h>
#include <UART.h>
#include <global.h>

extern void steer_init(void);

const unsigned char cmd1[]="test start\n";

static char Command_match(const unsigned char *p){
    int cmp=0;
    cmp=strcmp(UART_Rx_FIFO,cmd1);
    if(cmp==0)
    {
        UART_Tx_string("UART test cmd ok\n");
        return 1;
    }
    else
    {
        UART_Tx_string("you send cmd is error!\nplase try to send cmd:\ntest start\n");
        return 0;
    }
}

void RX_complete_handle(void){
    char temp;
    UART_Tx_string("you send:\n");
    UART_Tx_string(cmd1);

   if(Command_match(UART_Rx_FIFO)==1) {
       steer_init();
   }
}

void sample_end_handle(void){
    unsigned int i=0,j=0,temp=0;
    static int a=0;
    unsigned char *Tx_buffer;
    for ( i = 0; i < AD_sample_time; i++)
    {
        for ( j = 1; j < AD_sample_time;j++)
        {
            if(AD_value[i]>AD_value[j])
            temp = AD_value[i];
            AD_value[i] = AD_value[j];
            AD_value[j] = temp;
        }
    }
    unsigned int AD_sum=0;

    for ( i = 1; i < AD_sample_time-1; i++)
    {
        AD_sum+=AD_value[i];
    }
    AD_result=AD_sum/(AD_sample_time-2);

    sprintf(Tx_buffer,"LED:%2f ",AD_result);
    UART_Tx_string(Tx_buffer);
    a++;
    steer_turn(a);
}
