#include "system.h"

void ADC_init (void)
{
	ADC10CTL0 &= ~ENC; // Disable ADC
	ADC10CTL0 = SREF_0 + ADC10SHT_0 + REFON + ADC10ON + ADC10IE;
	ADC10CTL1 = INCH_10 + ADC10DIV_0 + CONSEQ_0 + ADC10SSEL_3;
}

unsigned int _readADC(unsigned int chan)
{

	ADC10CTL0 &= ~ENC;
	ADC10CTL0 = SREF_0 + ADC10SHT_0 + REFON + ADC10ON;
	ADC10CTL1 = chan + ADC10DIV_0 + CONSEQ_0 + ADC10SSEL_3;
	ADC10CTL0 |= ENC + ADC10SC;

	while (ADC10CTL1 & ADC10BUSY);
	return ADC10MEM;
}
