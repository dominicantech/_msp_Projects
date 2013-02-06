/***************************************************************
Programa: MSP_blinkLEDs.c
Rev: 1.0
Por: DominicanTech
Fecha: 1/20/2013

Descripción:
Este programa nos enseña como parpadear las LEDs utilizando el MSP430G2553.
Aqui tambien tenemos una simple configuracion del DCO (Digital Clock Osillator).

Placa MSP Dev by TI (Texas Instruments):
Placa: MSP-EXP430G2  $4.30
Code Composer Studio Ver. 5.3.0
****************************************************************/

#include <msp430g2553.h>

#define 	LED0 	BIT0	//Definimos BIT0 como LED0 (P1.0)
#define 	LED1	BIT6	//Definimos BIT6 como LED1 (P1.6)


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		//Paramos el WDT
	P1DIR |= LED0 + LED1;			//Configuramos el pin P1.0 como una salida

	//Configuracion del Clock DCO
	BCSCTL1 = CALBC1_8MHZ; 					//Configurar DCO a 8MHz
	DCOCTL = CALDCO_8MHZ; 					//Configurar la Modulation
	BCSCTL2 |= SELM_0 + DIVM_0 + DIVS_3;    //MCLK = DCO, SMCLK = MCLK/8

	while (1)		//El while loop
	{

		  P1OUT ^= LED0;		//Utilizamos el operador XOR para parpadear el LED0
		  P1OUT ^= LED1;		//Utilizamos el operador XOR para parpadear el LED1
		 // P1OUT ^= (LED1 + LED0);  //Tambien podriamos remplazar las dos lineas de arriba con solo esta.

/******************************************************************************************
*Enviamos un delay de 8000000 ciclos del clock DCO para un delay de 1Sec
*Esta no es la major manera de implementar un delay pero funciona.
		   ********************************************************************/
		  _delay_cycles(2000000);
	}
	
}
