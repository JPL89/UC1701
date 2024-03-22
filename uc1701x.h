/*
 * uc1701x.h
 *
 * Created: 01/03/2022 07:55:57
 *  Author: User
 */ 


#ifndef UC1701X_H_
#define UC1701X_H_

#define UC1701X_BIAS_RATIO			0x82
#define UC1701X_POWER_CONTROL		0x28	
#define UC1701X_SCROLL_LINE			0x40					 
#define UC1701X_VLCD_RATIO			0x20					 
#define UC1701X_ELETRONIC_VOLUME	0x81					 
#define UC1701X_ALL_PIXELS_ON		0x84					 
#define UC1701X_SET_INV_DISPLAY		0xA6					 
#define UC1701X_DISPLAY_OFF			0xAE
#define UC1701X_DISPLAY_ON			0xAF
#define UC1701X_SEG_DIRECTION		0xA0
#define UC1701X_COM_DIRECTION		0xC0
#define UC1701X_SYSTEM_RESET		0xE2
#define UC1701X_BOOST_RATIO			0xF8
#define UC1701X_ADV_CTRL_0			0xFA
#define UC1701X_ADV_CTRL_1			0xFB

unsigned char UC1701X_CURSOR_X;
unsigned char UC1701X_CURSOR_Y;

void UC1701X_Set_XY(unsigned char x, unsigned char y);
void UC1701X_Write(unsigned char data);
void UC1701X_Command(unsigned char data);
void UC1701X_Data(unsigned char data);
void UC1701X_SetCursor(unsigned char x, unsigned char y);
void UC1701X_Char(unsigned char c, const unsigned char Font[],unsigned char color);
void UC1701X_WriteStringXY(const char *data, unsigned char x, unsigned char y, const unsigned char Font[],unsigned char color);
void UC1701X_WriteIntXY(unsigned long num, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color);
void UC1701X_WriteFloatXY(double f, unsigned long prefix, unsigned char x, unsigned char y, const unsigned char Font[], unsigned int color);
void UC1701X_Init(void);	

#endif /* UC1701X_H_ */