#include <msp430g2553.h>
unsigned int _readADC(unsigned int chan);

#define     ldr_L       BIT4
#define     ldr_R       BIT5

	unsigned int _ldrL_ADCVal;
	unsigned int _ldrR_ADCVal;
	unsigned int _temp_ADCVal;

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 //Stop the WDT

		BCSCTL1 = CALBC1_8MHZ; 					//Set DCO Range, ACLK DIV/1, XTS Low-frequency mode.
		DCOCTL = CALDCO_8MHZ; 					//Set DCO Step and Modulation
		BCSCTL3 |= LFXT1S_0 + XCAP_3;           //LFXT1 = 32768-Hz crystal on LFXT1, ~12.5 pF
		BCSCTL2 |= SELM_0 + DIVM_0 + DIVS_3;    //MCLK = DCO, SMCLK = MCLK/8

	//Port select registers are in the device datasheet not in the fam datasheet.
	P1SEL |= BIT1 + BIT2;						//P1.1 = RxD, P1.2 = TxD
	P1SEL2 |= BIT1 + BIT2;						//P1.1 = RxD, P1.2 = TxD
	P1DIR |= BIT0 + BIT6;

	  UCA0CTL1 |= UCSSEL_2;						//SMCLK
	  UCA0BR0 = 104;                            // 1MHz 9600 (1MHz/9600bps)
	  UCA0BR1 = 0;                              // 1MHz 9600 (1MHz/9600bps)
	  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	  //_bis_SR_register(CPUOFF + GIE); // interrupts enabled

  while(1)
  {
	  //_delay_cycles(240);  					//Only used to allow internal ref to settle. (needs <30us) 1/8 = 125ns (125ns * 240 = 30uS)

	_ldrR_ADCVal = _readADC(INCH_4);
	_ldrL_ADCVal = _readADC(INCH_5);
	_temp_ADCVal = _readADC(INCH_10);

	  _delay_cycles(125000);
	  P1OUT ^= (BIT0 + BIT6);
	  _delay_cycles(125000);
	  UCA0TXBUF = _ldrR_ADCVal;
  }
}

unsigned int _readADC(unsigned int chan)
{

	ADC10CTL0 &= ~ENC; // Disable ADC
	ADC10CTL0 = SREF_0 + ADC10SHT_0 + REFON + ADC10ON;
	ADC10CTL1 = chan + ADC10DIV_0 + CONSEQ_0 + ADC10SSEL_3;
	ADC10CTL0 |= ENC + ADC10SC;             	// Enable and start conversion

	_delay_cycles(128);
	return ADC10MEM;
}

/**************************************************************************
// ADC10 Interrupt Service Routine

#pragma vector = ADC10_VECTOR
__interrupt void ADC10ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)

}

**************************************************************************/
