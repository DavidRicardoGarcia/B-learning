/*
 * GccApplication1.c
 *
 * Created: 18/10/2017 08:30:27 a.m.
 * Author : dmartinez
 */ 


#include <avr/interrupt.h>
#include "Mi_Lib.c"


char valor = 0x00;


int main(void){
	
	DDRB  = 0xFF;            			// PORTB como salida
	PORTB = 0X00;            			// Inicia PORTB en 0

	 // TIMER1
	 
	 asm("LDI R16,1<<2|0<<1|0<<0	; PRESCALER DE 256");
	 asm("STS 0x81,R16				; AQUÍ INICIA EL TIMER");	// 0x81 = TCCR1B
	 asm("LDI R16,0x0B				; SE PRECARGA EL TIMER 1");
	 asm("STS 0x85,R16				; CON 0x0BDC=3036");		// 0x85 = TCNT1H
	 asm("LDI R16,0xDC				; VALOR NECESARIO PARA");
	 asm("STS 0x84,R16				; DESBORDAR A 1 Seg");		// 0x84 = TCNT1L
	 asm("LDI R16,1<<0				; HABILITACIÓN DE INT");
	 asm("STS 0x6F,R16				; DE TIMER 1");				// 0x6F = TIMSK1
	 
	 sei();														// Interrupciones Globales


	
	while (1) {

	asm("NOP");

	}
	
}


ISR(TIMER1_OVF_vect){	// Subrutina de atención a la interrupción del Timer 1
	
	 asm("LDI R16,0x0B		; SE PRECARGA EL TIMER 1");
	 asm("STS 0x85,R16		; CON 0x0BDC=3036");		// 0x85 = TCNT1H
	 asm("LDI R16,0xDC		; VALOR NECESARIO PARA");
	 asm("STS 0x84,R16		; DESBORDAR A 1 Seg");		// 0x84 = TCNT1L

	valor = Sacar_Dato(valor);
	
}



