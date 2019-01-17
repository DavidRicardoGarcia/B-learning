/*
 * SquareSignalGenExample.cpp
 *
 * Created: 26/09/2018 3:46:29 p. m.
 * Author : esteban
 *
 * En este ejemplo se usa un microcontrolador de la familia tiny para generar una señal cuadrada.
 * 
 *
 */ 

#define F_CPU 9000000UL
#define _BV(bit) (1 << (bit))


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    
	// se pone el pin 3 como salida digital.
	DDRB |= _BV(3);
	
    while (1) 
    {
		// retardo de n milisegundos
		_delay_ms(5);
		PORTB ^= _BV(3);
    }
}

