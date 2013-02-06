#include "system.h"

void UART_init (void)
{
	  UCA0CTL1 |= UCSSEL_2;						//SMCLK
	  UCA0BR0 = 104;                            // 1MHz 9600 (1MHz/9600bps)
	  UCA0BR1 = 0;                              // 1MHz 9600 (1MHz/9600bps)
	  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void UART_puts(char * s)
{
		while (*s)
		{
		while (!(IFG2 & UCA0TXIFG));
		UCA0TXBUF = *s++;
		}
}

void UART_outdec(long data, unsigned char ndigits)
{
	unsigned char sign, s[6];
	unsigned int i;
	sign = ' ';
	if(data < 0)
		{
		sign='-';
		data = -data;
		}
	i = 0;

	do {
		s[i++] = data % 10 + '0';
		if(i == ndigits)
			{
			s[i++]='.';
			}
	   }

	while((data /= 10) > 0);
	s[i] = sign;
	do 	{
		while (!(IFG2&UCA0TXIFG));
		UCA0TXBUF = s[i];
		}
	while(i--);
}

