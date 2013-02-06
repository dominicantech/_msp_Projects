#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <msp430g2553.h>
#include <stdio.h>

void UART_outdec(long data, unsigned char ndigits);
void UART_puts(char * s);
void UART_init (void);
void CLK_init(void);
void ADC_init (void);
unsigned int _readADC(unsigned int chan);
void SYS_init(void);
void PWM_init(void);
void PWM_dutySet(unsigned int L_Motor, unsigned int R_Motor);

#endif
