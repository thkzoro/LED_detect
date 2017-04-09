/*
 * SPI.h
 *
 *  Created on: 2013-4-3
 *      Author: Administrator
 */

#ifndef SPI_H_
#define SPI_H_

//#define soft_SPI
#define hard_SPI

#define     SPI_SCLK_Set()     P1OUT |= BIT5
#define     SPI_SCLK_Clr()     P1OUT &= ~BIT5

#define     SPI_SDIN_Set()     P1OUT |= BIT7
#define     SPI_SDIN_Clr()     P1OUT &= ~BIT7

#define     SPI_CS_Set()       P1OUT |= BIT4
#define     SPI_CS_Clr()       P1OUT &= ~BIT4

void SPI_init(void);
char  SPI_Tx_char(unsigned char *Ptr);
#endif /* SPI_H_ */
