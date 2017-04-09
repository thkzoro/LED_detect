//              GND    电源地
//              VCC  接5V或3.3v电源
//              SCL   P1.5
//              SDA   P1.7
//              RES  接P3.0
//              DC   接P3.1
//              CS   接P1.4----本模块已经帮用户接地，无需再接
//              ----------------------------------------------------------------
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include <msp430g2553.h>
#include	<intrinsics.h> 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据



#define		OLED_SCLK_Set()		SPI_SCLK_Set()
#define		OLED_SCLK_Clr()		SPI_SCLK_Clr()

#define		OLED_SDIN_Set()		SPI_SDIN_Set()
#define		OLED_SDIN_Clr()		SPI_SDIN_Clr()

#define		OLED_DC_Set()   	P3OUT |= BIT1
#define		OLED_DC_Clr() 		P3OUT &= ~BIT1

#define		OLED_CS_Set()   	SPI_CS_Set()
#define		OLED_CS_Clr()		SPI_CS_Clr()

#define		OLED_RST_Set()		P3OUT |= BIT0
#define		OLED_RST_Clr()		P3OUT &= ~BIT0

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   



 		     

//OLED控制用函数
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
void OLED_Fill(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char dot);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2);
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
//void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



