#include "system.h"
unsigned int ADCVal;

void UART_outdec(long data, unsigned char ndigits);

//Variables to store ADC Values
unsigned int _ldrL_ADCVal;
unsigned int _ldrR_ADCVal;

int main(void)
{
	CLK_init();
	SYS_init();
	UART_init();
	ADC_init();
	PWM_init();			//Initialize PWM (servos not running)
	PWM_dutySet(500, 200);

	_bis_SR_register(LPM0_bits + GIE); // interrupts enabled

	while(1)
	{

		//_ldrL_ADCVal = _readADC(INCH_4); 		//Read ADC input on P2.1
		//_ldrR_ADCVal = _readADC(INCH_5); 		//Read ADC input on P2.2

		UART_puts((char *)"\n\r");
		UART_puts((char *)"_ldrL_ADCVal: ");
		UART_outdec(_ldrL_ADCVal, 0);
		UART_puts((char *)"\n\r");
		UART_puts((char *)"_ldrR_ADCVal: ");
		UART_outdec(_ldrR_ADCVal, 0);

		_delay_cycles(125000);
		P1OUT ^= (BIT0 + BIT6);
	}
}

