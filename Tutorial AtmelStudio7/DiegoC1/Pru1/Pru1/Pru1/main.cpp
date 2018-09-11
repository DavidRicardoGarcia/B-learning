/*
 * Pru1.cpp
 *
 * Created: 15/07/2016 02:32:36 p.m.
 * Author : dmartinez
 */ 

//#include <Arduino.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


int incrementar (int x);


int main(void) {
	
	int y,z;
	
	y = 0;
	
	DDRB = 0xff ;
	
	while (1) {
	
		PORTB= 0xff;
		_delay_ms(500);
	
		PORTB = 0x00;
		_delay_ms(500);
	
		z=incrementar(y);
	
	}
}


int incrementar (int x){
	
	x++;
	
	return(x);
	
}
