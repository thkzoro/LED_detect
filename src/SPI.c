#include <msp430.h>
#include <SPI.h>

void SPI_Tx_IRQHandler(void){
    IFG2 &= ~UCB0TXIFG;

}
void SPI_Rx_IRQHandler(void){

}

#ifdef hard_SPI
extern void USCI_B0_init(void);
extern void SPI_GPIO_init(void);

char  SPI_Tx_char(unsigned char *Ptr){
    if(UCB0STAT & UCBUSY)   return  (1);            // 判断硬件SPI正忙，返回0
    SPI_CS_Clr();
    UCB0TXBUF = *Ptr;
    LPM0;
    while((UCB0STAT & UCBUSY));
    SPI_CS_Set();
    return (0);
}



void SPI_init(void){
    SPI_GPIO_init();
    USCI_B0_init();
}
#endif  //end of HARD_SPI

#ifdef soft_SPI
char  SPI_Tx_char(unsigned char *Ptr){
    unsigned char temp,i;
    temp=*Ptr;
    SPI_CS_Clr();
    for(i=0;i<8;i++)
    {
        SPI_SCLK_Clr();
        if(temp & BIT7)
        {
            SPI_SDIN_Set();
        }
        else
            SPI_SDIN_Clr();

        SPI_SCLK_Set();
        temp<<=1;
    }
    SPI_CS_Set();
    return 0;
}

void SPI_init(void){
    P1DIR |= BIT4 | BIT5 | BIT6 | BIT7;
    P1OUT &= ~(BIT4 | BIT5 | BIT6 | BIT7);
}

#endif
