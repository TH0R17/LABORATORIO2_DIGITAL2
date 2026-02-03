#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD/LCD.h"
#include "ADC/ADC.h"
#include "UART/UART.h"

char buffer[20];
int16_t contador = 0;

int main(void)
{
	uint16_t adc_s1, adc_s2;
	uint16_t mv;
	uint8_t v_ent, v_dec;
	char rx;

	initLCD8bits();
	ADC_Init();
	UART_Init(9600);

	while (1)
	{
		/* ======== S1 ======== */
		adc_s1 = ADC_Read(0);
		mv = (adc_s1 * 5000UL) / 1023;
		v_ent = mv / 1000;
		v_dec = (mv % 1000) / 10;

		LCD_Set_Cursor(1,1);
		sprintf(buffer, "S1:%d.%02dV", v_ent, v_dec);
		LCD_Write_String(buffer);

		/* ======== S2 ======== */
		adc_s2 = ADC_Read(3);

		LCD_Set_Cursor(1,2);
		sprintf(buffer, "S2:%4d S3:%3d", adc_s2, contador);
		LCD_Write_String(buffer);

		/* ======== UART TX ======== */
		sprintf(buffer, "S1=%d.%02dV S2=%d S3=%d\r\n",
		v_ent, v_dec, adc_s2, contador);
		UART_TxString(buffer);

		/* ======== UART RX ======== */
		if (UART_DataAvailable())
		{
			rx = UART_RxChar();

			if (rx == '+') contador++;
			if (rx == '-') contador--;
		}

		_delay_ms(500);
	}
}