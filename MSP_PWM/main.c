#include <msp430g2553.h>

void main(void){

    WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

	BCSCTL1 = CALBC1_8MHZ; 					//Set DCO Range, ACLK DIV/1, XTS Low-frequency mode.
	DCOCTL = CALDCO_8MHZ; 					//Set DCO Step and Modulation
	BCSCTL3 |= LFXT1S_0 + XCAP_3;           //LFXT1 = 32768-Hz crystal on LFXT1, ~12.5 pF
	BCSCTL2 |= SELM_0 + DIVM_0 + DIVS_3;    //MCLK = DCO, SMCLK = MCLK/8 = 1MHz

			P2DIR |= BIT1 + BIT4;			//P2.1 and P2.4 as PWM output
            P2SEL |= BIT1 + BIT4;			//P2.1 and P2.2 options select as PWM

            TA1CCR0 = 4999;					//PWM period for TA1

            TA1CCR1 = 200;					//TA1 PWM duty cycle
            TA1CCR2 = 500;					//TA2 PWM duty cycle

            TA1CCTL2 = OUTMOD_7;			//TA2 output mode reset/set
            TA1CCTL1 = OUTMOD_7;			//TA1 output mode reset/set
            TA1CTL = TASSEL_2 + MC_1 + ID_2;
            //_BIS_SR(LPM0_bits + GIE);                   				//Enter Low power mode 0
}
