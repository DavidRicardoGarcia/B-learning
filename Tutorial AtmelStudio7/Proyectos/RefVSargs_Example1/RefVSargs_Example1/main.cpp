/*
 * RefVSargs_Example1.cpp
 *
 * Created: 25/09/2018 3:38:07 p. m.
 * Author : esteban
 
 * En este ejemplo se muestra una comparacion en desempeño para dos casos diferentes cuando se invoca un funcion.
 * hay 2 formas, la primera es pasar todos los argumentos a la fucion (cuando se habla de arreglos.)
 * la otra opcion es pasar un apuntador que indica la posicion del arreglo en memoria. 
 
 * la ventaja de la primera opcion es que es mas segura para preservar la informacion, ya que se hace una copia de los 
 * cuando se va a iniciar la rutina. El problema de lo anterior es que hacer la copia de cada uno de los argumentos
 * va a consumir tiempo de computo.
 
 * por otro lado cuando se pasa el apuntador no existe este inconveniente, la desventaja es que la informacion original 
 * puede ser alterada desde el metodo.
 
 */ 

#define F_CPU 464UL //(500Khz) macro para definir la frecuencia de trabajo del microcontrolador. se usa en la implementacion del comando delay.

#include <avr/io.h>

#include <avr/io.h>
#include <avr/interrupt.h> // libreria de AVR que facilita uso de interrupciones
#include <util/delay.h>

// #define _BV( bit ) ( 1<<(bit) ) // macro para facilitar la escritura de los comandos para leer y escribir sobre registros del microcontrolador.

				
				
int mit_zeiger(double *p);
int kein_zeiger(double Ar[192]);


int main(void)
{
	
	// coeficientes del filtro FIR
	double FIR[] = {-1000, 2000, 3000, 40000,
					-100, 244, 355, 455,
					-1555, 2777, 377, 47,
					-1111, 2888, 3888, 4555,
					-11234, 2432, 364, 2004,
					-1347, 23754, 33456, 46345,
					-1567, 2987, 3263, 452345,
					-15678, 27878, 35867, 45345,
					-15678, 28765, 38768, 45876,
					-16587, 26875, 35876, 47568,
					-17658, 25867, 358, 485,
					-15987, 22352, 35245, 4542534,
					
					-1000, 2000, 3000, 40000,
					-100, 244, 355, 455,
					-1555, 2777, 377, 47,
					-1111, 2888, 3888, 4555,
					-11234, 2432, 364, 2004,
					-1347, 23754, 33456, 46345,
					-1567, 2987, 3263, 452345,
					-15678, 27878, 35867, 45345,
					-15678, 28765, 38768, 45876,
					-16587, 26875, 35876, 47568,
					-17658, 25867, 358, 485,
					-15987, 22352, 35245, 4542534,
					
					-1000, 2000, 3000, 40000,
					-100, 244, 355, 455,
					-1555, 2777, 377, 47,
					-1111, 2888, 3888, 4555,
					-11234, 2432, 364, 2004,
					-1347, 23754, 33456, 46345,
					-1567, 2987, 3263, 452345,
					-15678, 27878, 35867, 45345,
					-15678, 28765, 38768, 45876,
					-16587, 26875, 35876, 47568,
					-17658, 25867, 358, 485,
					-15987, 22352, 35245, 4542534,
					
					-1000, 2000, 3000, 40000,
					-100, 244, 355, 455,
					-1555, 2777, 377, 47,
					-1111, 2888, 3888, 4555,
					-11234, 2432, 364, 2004,
					-1347, 23754, 33456, 46345,
					-1567, 2987, 3263, 452345,
					-15678, 27878, 35867, 45345,
					-15678, 28765, 38768, 45876,
					-16587, 26875, 35876, 47568,
					-17658, 25867, 358, 485,
					-15987, 22352, 35245, 4542534					
	};
	
	
	// pin 0 del puerto C como salida digital.
	DDRC |= _BV(0);
	
	double *p = FIR; // se obtiene el apuntador del arreglo de 480 elementos.
	
    while (1) 
    {
		int k;
		if( PINC&_BV(1) ){
				k = mit_zeiger(p);
		} else {
				k = kein_zeiger(FIR);
		}
    }
}



// con apuntador.
int mit_zeiger(double *p){
	PORTC ^= _BV(0);
	return 1;
};


// pasando el arreglo completo.
int kein_zeiger(double Ar[192]){
	PORTC ^= _BV(0);
	return 1;
};
