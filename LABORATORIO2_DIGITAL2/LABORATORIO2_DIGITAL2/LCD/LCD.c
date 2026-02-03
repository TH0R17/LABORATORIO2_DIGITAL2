/*
Autor:Nesthor Guillermo
Descripción: Libreria LCD

*/


#include "LCD.h"

void initLCD8bits(void)
{
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4);

	PORTD = 0;
	PORTB = 0;

	_delay_ms(20);

	LCD_CMD(0x30);
	_delay_ms(5);

	LCD_CMD(0x30);
	_delay_ms(5);

	LCD_CMD(0x30);
	_delay_ms(5);

	LCD_CMD(0x38); // 8 bits, 2 líneas
	_delay_ms(5);

	LCD_CMD(0x0C); // Display ON
	_delay_ms(5);

	LCD_CMD(0x01); // Clear
	_delay_ms(5);

	LCD_CMD(0x06); // Increment cursor
}

void LCD_CMD(char a)
{
	PORTD &= ~(1<<PORTD2); // RS = 0
	PORTD &= ~(1<<PORTD3); // RW = 0
	LCD_Port(a);

	PORTD |= (1<<PORTD4);  // E = 1
	_delay_us(10);
	PORTD &= ~(1<<PORTD4); // E = 0

	_delay_ms(5);
}

void LCD_Port(char a)
{
	// D0 ? D5 ? PD5
	(a & (1<<0)) ? (PORTD |= (1<<PD5)) : (PORTD &= ~(1<<PD5));

	// D1 ? D6 ? PD6
	(a & (1<<1)) ? (PORTD |= (1<<PD6)) : (PORTD &= ~(1<<PD6));

	// D2 ? D7 ? PD7
	(a & (1<<2)) ? (PORTD |= (1<<PD7)) : (PORTD &= ~(1<<PD7));

	// D3 ? D8 ? PB0
	(a & (1<<3)) ? (PORTB |= (1<<PB0)) : (PORTB &= ~(1<<PB0));

	// D4 ? D9 ? PB1
	(a & (1<<4)) ? (PORTB |= (1<<PB1)) : (PORTB &= ~(1<<PB1));

	// D5 ? D10 ? PB2
	(a & (1<<5)) ? (PORTB |= (1<<PB2)) : (PORTB &= ~(1<<PB2));

	// D6 ? D11 ? PB3
	(a & (1<<6)) ? (PORTB |= (1<<PB3)) : (PORTB &= ~(1<<PB3));

	// D7 ? D12 ? PB4
	(a & (1<<7)) ? (PORTB |= (1<<PB4)) : (PORTB &= ~(1<<PB4));
}

void LCD_Write_Char(char c)
{
	PORTD |= (1<<PORTD2); // RS = 1
	PORTD &= ~(1<<PORTD3); // RW = 0
	LCD_Port(c);

	PORTD |= (1<<PORTD4);
	_delay_us(10);
	PORTD &= ~(1<<PORTD4);

	_delay_ms(5);
}

void LCD_Write_String(char *str)
{
	while (*str)
	{
		LCD_Write_Char(*str);
		str++;
	}
}
void LCD_Set_Cursor(char col, char row)
{
	char address;
	if(row == 1)
	address = 0x80 + col - 1;
	else
	address = 0xC0 + col - 1;

	LCD_CMD(address);
}