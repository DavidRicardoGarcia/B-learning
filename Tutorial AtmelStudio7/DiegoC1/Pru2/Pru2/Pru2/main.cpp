/*
 * Pru2.cpp
 *
 * Created: 18/07/2016 09:39:37 a.m.
 * Author : dmartinez
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define OFFSET 0x4000

int main(void){
	
unsigned char *p1 = (unsigned char *) (OFFSET + 1);
unsigned char *p2 = (unsigned char *) (OFFSET + 2);

//	DDRA = 0xFF;	// Dirección de los puertos
//	DDRC = 0xFF;	
//	DDRG = 0xFF;	
	
	XMCRB = 0x00;	// Habilitar todo el bus de direcciones

	XMCRA = 0x80;	// Habilita Memoria Externa

	for (;;){

		*p1 = 0xaa;
		_delay_ms(1);
	
		*p2 = 0x55;
		_delay_ms(1);

	}
	
}