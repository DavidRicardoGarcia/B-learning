/*
 * DebuggingExample1.cpp
 *
 * Created: 31/08/2018 5:05:14 p. m.
 * Author : esteban
 * YouTube Channel :
 * 
 * Este proyecto se creo para hacer una demostracion de las capacidades de depuracion del JTAGICE3.
 * Para ello se configuro una interrupcion por desbordamiento de temporizador 1
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> // libreria de AVR que facilita uso de interrupciones

#define F_CPU 4000000UL //(1Mhz) macro para definir la frecuencia de trabajo del microcontrolador. se usa en la implementacion del comando delay.
// #define _BV( bit ) ( 1<<(bit) ) // macro para facilitar la escritura de los comandos para leer y escribir sobre registros del microcontrolador.
#define COUNTER_INIT 61630 // valor a partir del cual debe empezar a contar el temporizador.




int main(void)
{
	DDRC |= _BV(0); // se establece el pin PC0 como salida digital
	PORTC |= _BV(0);
	
	sei(); // funcion que configura registros para habilitar interrupciones.
	TCNT1 = COUNTER_INIT; // se inicializa el temporizador en 616630
	TIMSK |= _BV(7); // se habilita la interrupcion de overflow en temporizador 1
	TCCR1B |= _BV(2) | _BV(0); // se establece fuente de reloj con preescalamiento de 1024
	
	int a = 0;
	
    while (1) 
    {
		// este incremento de la variable "a" no tiene ninguna funcionalidad
		// solo se agrega para mostrar la observacion de variables durante el 
		// proceso de debugging
		a++;
		if(a == 10000){
			a=0;
		}
    }
}

// rutina de interrupcion cuando se desborda el temporizador 1
ISR(TIMER1_OVF_vect){
	TCNT1 = COUNTER_INIT; // se recarga nuevamente el temporizador en 61630
	PORTC ^= _BV(0); // se articula el valor del bit 0 en el puerto C.
}
