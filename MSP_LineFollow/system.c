#include "system.h"

void CLK_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;               //Stop the WDT
	BCSCTL1 = CALBC1_8MHZ; 					//Set DCO Range, ACLK DIV/1, XTS Low-frequency mode.
	DCOCTL = CALDCO_8MHZ; 					//Set DCO Step and Modulation
	BCSCTL3 |= LFXT1S_0 + XCAP_3;           //LFXT1 = 32768-Hz crystal on LFXT1, ~12.5 pF
	BCSCTL2 |= SELM_0 + DIVM_0 + DIVS_3;    //MCLK = DCO, SMCLK = MCLK/8
}

void SYS_init(void)
{
	//Configure Port1
	P1DIR |= BIT0 + BIT6;					//Sets P1.0 and P1.6 as Outputs

	P1SEL |= BIT1 + BIT2;						//P1.1 = RxD, P1.2 = TxD
	P1SEL2 |= BIT1 + BIT2;						//P1.1 = RxD, P1.2 = TxD

	//Configure Port2
	P2DIR |= BIT1 + BIT4;			//P2.1 and P2.4 as PWM output
    P2SEL |= BIT1 + BIT4;			//P2.1 and P2.2 options select as PWM
}
