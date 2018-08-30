/*
 * Ejemplo1Cpp_Blink.cpp
 *
 * Created: 29/08/2018 2:54:41 p. m.
 * Author : raul esteban alzate aristizabal
 * YouTubeChannel: 
 * Instagram: RoughGentleman77
 
 En este proyecto de ejemplo se realiza el parpadeo de un led cada 1 segundo.
 */ 

#include <avr/io.h> 

#define F_CPU 4000000UL //(1Mhz) macro para definir la frecuencia de trabajo del microcontrolador. se usa en la implementacion del comando delay.

//#define _BV( bit ) ( 1<<(bit) ) // macro para facilitar la escritura de los comandos para leer y escribir sobre registros del microcontrolador.

#include <util/delay.h> // libreria de AVR para hacer retardos.

int main(void)
{
    DDRB |= _BV(1); // se asigna el pin 1 del puerto B como salida digital
    while (1) 
    {
		PORTB |= _BV(1); // se asigna un valor logico alto a PB1
		_delay_ms(1000); // un retardo de 1000 ms
		PORTB &= ~_BV(1); // se asigna un nivel logico bajo a PB1
		_delay_ms(1000); // se hace un retardo de 1000 ms
    }
}

