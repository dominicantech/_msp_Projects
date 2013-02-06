// MSP430 PushButton that toggles LEDs On and Off
//
// Description: PushButton in P1.3 through interrupt turns on and off the LED at P1.0
// and P1.6.  By changing the P1.3 interrupt edge, the interrupt is called every time
// the button is pushed and pulled; toggling the LED everytime.

#include <msp430g2553.h>

#define LED1 BIT0
#define LED2 BIT6
#define BUTTON BIT3

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;// Stop watchdog timer
    P1DIR |= (LED1 + LED2); // Set LEDs to output direction
                            // P1.3 must stay at input (this is the default)
    P1OUT &= ~(LED1 + LED2); // turn LEDs off
    P1IE |= BUTTON; // P1.3 interrupt enabled
    P1IFG &= ~BUTTON; // P1.3 IFG cleared

    __enable_interrupt(); // enable all interrupts
    for (;;)
        /* endless loop */ ;
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= (LED1 + LED2); // LED toggle
    P1IFG &= ~BUTTON; // P1.3 IFG cleared
    P1IES ^= BUTTON; // toggle the interrupt edge,
    // the interrupt vector will be called
    // when P1.3 goes from High to Low as well as
    // Low to High
}
