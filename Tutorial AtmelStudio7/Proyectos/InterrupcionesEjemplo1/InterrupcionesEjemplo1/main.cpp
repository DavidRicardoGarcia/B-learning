/*
 * InterrupcionesEjemplo1.cpp
 *
 * Created: 30/08/2018 1:52:48 p. m.
 * Author : esteban
 * Instagram : RoughGentleman77
 * YouTube Channel : 
 * En este proyecto de atmel estudio se hace una desmotracion de una interrupcion por desbordamiento de temporizador.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> // libreria de AVR que facilita uso de interrupciones

#define F_CPU 4000000UL //(1Mhz) macro para definir la frecuencia de trabajo del microcontrolador. se usa en la implementacion del comando delay.
// #define _BV( bit ) ( 1<<(bit) ) // macro para facilitar la escritura de los comandos para leer y escribir sobre registros del microcontrolador.
#define COUNTER_INIT 61630 // valor a partir del cual debe empezar a contar el temporizador.

int main(void)
{
	DDRB |= _BV(1); // se establece el pin PB1 como salida digital
	
	sei(); // funcion que configura registros para habilitar interrupciones.
	TCNT1 = COUNTER_INIT; // se inicializa el temporizador en 616630
	TIMSK |= _BV(2); // se habilita la interrupcion de overflow en temporizador 1
	TCCR1B |= _BV(2) | _BV(0); // se establece fuente de reloj con preescalamiento de 1024
	
	
    while (1) 
    {
		// se queda enganchado en el while sin hacer nada.
    }
}

// rutina de interrupcion cuando se desborda el temporizador 1
ISR(TIMER1_OVF_vect){
	TCNT1 = COUNTER_INIT; // se recarga nuevamente el temporizador en 61630
	PORTB ^= _BV(1);
}

