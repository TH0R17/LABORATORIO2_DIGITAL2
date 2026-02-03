/*
Autor:Nesthor Guillermo
Descripción: Libreria LCD

*/
#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void initLCD8bits(void);
void LCD_Port(char a);
void LCD_CMD(char a);
void LCD_Write_Char(char c);
void LCD_Write_String(char *a);
void LCD_Shift_Right(void);
void LCD_Shift_Left(void);
void LCD_Set_Cursor(char c, char f);

#endif