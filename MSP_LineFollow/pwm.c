#include "system.h"

void PWM_init(void)
{

  TA1CCR0 = 5000;                   		//PWM period for TA1
  TA1CCTL1 = OUTMOD_7;              		//CCR2 reset/set
  TA1CCR1 = 375;                    		//CCR1 PWM duty cycle (450/250Khz) = 1.8ms
  TA1CCTL2 = OUTMOD_7;            			//CCR2 reset/set
  TA1CCR2 = 375;                 			//CCR2 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_1 + ID_2;  		//Up Mode, SMCLK = 1MHz, TA1 Clock Div by 4 = (SMCLK 1MHz / 4 = TA1 Clk = 250KHz)

}

void PWM_dutySet(unsigned int L_Motor, unsigned int R_Motor)
{
  TA1CCR1 = L_Motor;                    		//CCR1 PWM duty cycle (450/250Khz) = 1.8ms
  TA1CCR2 = R_Motor;                  			//CCR2 PWM duty cycle
}

