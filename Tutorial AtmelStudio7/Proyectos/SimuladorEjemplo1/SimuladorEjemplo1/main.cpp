/*
 * SimuladorEjemplo1.cpp
 *
 * Created: 24/08/2018 6:16:31 p. m.
 * Author : Raul Esteban Alzate A.
 * whatsapp: 3135158611
 * insta: roughgentleman77
 
 
 en este proyecto se hacce una demostracion del simulador de atmel estudio para el ejemplo de hacer parpadear un led.
 */ 

#include <avr/io.h> // libreria basica para trabajar con microcontroladores AVR.

#include <util/delay.h>

#define F_CPU 1000000UL //(1Mhz) macro para definir la frecuencia de trabajo del microcontrolador. se usa en la implementacion del comando delay.

#define _BV( bit ) ( 1<<(bit) ) // macro para facilitar la escritura de los comandos para leer y escribir sobre registros del microcontrolador.


int main(void)
{
	
	DDRB |= _BV(0);
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB|= _BV(1);
		_delay_us(5); // retardo de 16us
		PORTB&= ~_BV(1);
		_delay_us(5);
    }
}

