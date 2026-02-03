/*
 * UART.h
 *
 * Created: 1/02/2026 18:25:15
 *  Author: Usuario
 */ 
#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


void UART_Init(unsigned long baud);
void UART_TxChar(char c);
void UART_TxString(char *str);
char UART_RxChar(void);
uint8_t UART_DataAvailable(void);

#endif