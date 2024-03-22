/*
 * uc1701x.cpp
 *
 * Created: 01/03/2022 07:55:46
 *  Author: User
 */ 

#include <xc.h>

#include "uc1701x.h"

#define UC1701X_CS_HIGH         PORTCbits.RC0 = 1
#define UC1701X_CS_LOW          PORTCbits.RC0 = 0

#define UC1701X_CD_HIGH         PORTCbits.RC1 = 1
#define UC1701X_CD_LOW          PORTCbits.RC1 = 0

#define UC1701X_SCK_HIGH        PORTCbits.RC2 = 1
#define UC1701X_SCK_LOW         PORTCbits.RC2 = 0

#define UC1701X_SDI_HIGH        PORTCbits.RC3 = 1
#define UC1701X_SDI_LOW         PORTCbits.RC3 = 0

void UC1701X_Write(unsigned char data)
{
    for (unsigned char mask = 0; mask; mask >>= 1)
    {
        UC1701X_SCK_LOW;

        if(data & mask) UC1701X_SDI_HIGH; else UC1701X_SDI_LOW;

        UC1701X_SCK_HIGH;
    }
}
void UC1701X_Command(unsigned char data)
{
    UC1701X_CD_LOW;
    UC1701X_CS_LOW;

    UC1701X_Write(data);

    UC1701X_CS_HIGH;
}

void UC1701X_Data(unsigned char data)
{
    UC1701X_CD_HIGH;
    UC1701X_CS_LOW;

    UC1701X_Write(data);

    UC1701X_CS_HIGH;	
}
void UC1701X_SetCursor(unsigned char x, unsigned char y)
{
    UC1701X_Command(0xB0 | y);
    UC1701X_Command(0x10 | (x >> 4));
    UC1701X_Command(0x0F & x);
}
void UC1701X_Set_XY(unsigned char x, unsigned char y)
{
    UC1701X_CURSOR_X = x;
    UC1701X_CURSOR_Y = y;
}
void UC1701X_Char(unsigned char data, const unsigned char Font[],unsigned char color)
{
    unsigned char wd				= Font[0]; // font width
    unsigned char pg				= Font[2]; // font pages
    unsigned char st				= Font[3]; // font start
    unsigned char ch				= 0; // character
    unsigned char fh				= 5; // font header size
    int row							= 0; // row
    int col							= 0; // col
    int i							= 0; // loop

    int font_data_w_h 	= (2*(data-st));
    int font_data_pos	= (wd*pg) * (data-st);

    int id = (font_data_pos + font_data_w_h) + fh;

    unsigned char char_w = Font[id++] ;
    id++;

    for (col=0; col<pg; col++)
    {
        UC1701X_SetCursor(UC1701X_CURSOR_X, UC1701X_CURSOR_Y + col);

        for (row=0; row < wd; row++)
        {
                ch = Font[ ( id + row + i) ];

                UC1701X_Data( ch ^ color);
        }

        i += wd;
    }

    UC1701X_CURSOR_X += char_w + 1;	
}
void UC1701X_WriteStringXY(const char *data, unsigned char x, unsigned char y, const unsigned char Font[],unsigned char color)
{
    UC1701X_CURSOR_X = x;
    UC1701X_CURSOR_Y = y;

    while(*data)
    {
        UC1701X_Char(*data++, Font,color);
    }
}

void UC1701X_Init(void)
{
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC2 = 0;
    TRISCbits.RC3 = 0;
	
    UC1701X_CS_HIGH;

    UC1701X_Command( UC1701X_BIAS_RATIO | 1 );
    UC1701X_Command( UC1701X_ELETRONIC_VOLUME | 5 );
    UC1701X_Command( UC1701X_SEG_DIRECTION | 1 );
    //Command( UC1701X_COM_DIRECTION | 0 );
    UC1701X_Command( UC1701X_DISPLAY_ON );
}

