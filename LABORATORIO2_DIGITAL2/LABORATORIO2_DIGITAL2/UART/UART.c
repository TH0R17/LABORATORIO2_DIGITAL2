/*
 * UART.c
 *
 * Created: 1/02/2026 18:25:03
 *  Author: Usuario
 */ 
#include "UART.h"

void UART_Init(unsigned long baud)
{
	uint16_t ubrr = (F_CPU / (16UL * baud)) - 1;

	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void UART_TxChar(char c)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void UART_TxString(char *str)
{
	while (*str)
	{
		UART_TxChar(*str++);
	}
}

uint8_t UART_DataAvailable(void)
{
	return (UCSR0A & (1 << RXC0));
}

char UART_RxChar(void)
{
	return UDR0;
}