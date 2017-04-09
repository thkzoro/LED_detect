#ifndef UART_INIT_H_
#define UART_INIT_H_

#define    UART_Rx_FIFO_size 16
#define    UART_Tx_FIFO_size 8

struct Tx_FIFO
{
    unsigned short  empty;
    unsigned char   *UART_Tx_FIFO;
};

struct Tx_FIFO  tx_f[UART_Tx_FIFO_size];

unsigned char   UART_Rx_FIFO[UART_Rx_FIFO_size];

extern void USCI_A0_init(void);
void UART_Tx_string(unsigned char *Ptr);

#endif /* UART_INIT_H_ */
