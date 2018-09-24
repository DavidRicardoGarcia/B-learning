/*
 * FiltroDigitalEjemplo1.cpp
 *
 * Created: 17/09/2018 4:24:49 p. m.
 * Author : raul esteban alzate
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> // libreria de AVR que facilita uso de interrupciones

#define F_CPU 4000000UL //(1Mhz) macro para definir la frecuencia de trabajo del microcontrolador. se usa en la implementacion del comando delay.
// #define _BV( bit ) ( 1<<(bit) ) // macro para facilitar la escritura de los comandos para leer y escribir sobre registros del microcontrolador.
#define COUNTER_INIT 61536 // valor a partir del cual debe empezar a contar el temporizador.

// referencia de tension para el ADC. (se debe reemplazar por el valor en tension que se va a utilliar).
#define ADC_REF 2.56


// coeficientes del filtro FIR
double FIR[] = {-0.00128380297866020, -0.00132399486984157, 0.000874051194962120, 0.00518832470467140, 
				0.00810033142850478, 0.00521435647752571, -0.00383759191001733, -0.0130617913066840,
				-0.0144823190219763, -0.00642101723421765, 0.00313914084679193, 0.00398182413302851,
				-0.00377232760690022, -0.00607061854849465, 0.0117264683573292, 0.0446289841467845,
				 0.0629963601398514, 0.0346660062390859, -0.0407342672859202, -0.118248982958290,
				-0.134988177907574, -0.0618228722171959, 0.0645157002731517, 0.161472913942402,
				 0.161472913942402, 0.0645157002731517, -0.0618228722171959, -0.134988177907574,
				-0.118248982958290, -0.0407342672859202, 0.0346660062390859, 0.0629963601398514,
				 0.0446289841467845, 0.0117264683573292, -0.00607061854849465, -0.00377232760690022,
				 0.00398182413302851, 0.00313914084679193, -0.00642101723421765, -0.0144823190219763, 
				-0.0130617913066840, -0.00383759191001733, 0.00521435647752571, 0.00810033142850478,
				 0.00518832470467140, 0.000874051194962120, -0.00132399486984157, -0.00128380297866020};

// Global variables and static variables are automatically initialized to zero
double window[48];				 

// lectura actual del ADC
double read;

// salida
double out;


int main(void)
{
	// todo el puerto B se usara como salida digital (se tendra una salida de 8 bits)
	DDRB = 0xff;
	
	TCNT1 = COUNTER_INIT; // se inicializa el temporizador en 616630
	TIMSK1 |= _BV(2); // se habilita la interrupcion de overflow en temporizador 1
	TCCR1B |= _BV(0); // se establece fuente de reloj sin preescalamiento
	sei(); // funcion que configura registros para habilitar interrupciones.
	
	// se configura el ADC
	ADCSRA |= _BV(7)|_BV(2)|_BV(0); // se habilita el adc y se pone preescalador de 32
	// en este proyecto se uso un oscilador de cristal de 4Mhz. De acuerdo a la frecuencia que se emplee se deben escoger los preescaladores
	// ya que el ADC del micro tiene una frecuencia limite que se debe verificar en la respectiva ficha tecnica.
	
	// se configura la salida para el DAC
	
    while (1) 
    {
		// solo se ejecutan instrucciones en la rutina de interrupcion.
    }
}

// rutina de interrupcion cuando se desborda el temporizador 1
ISR(TIMER1_OVF_vect){
	TCNT1 = COUNTER_INIT; // se recarga nuevamente el temporizador en 61630
	
	// se actualiza la ventana deslizante.
	for( int i=47; i>0 ; i-- ){
		window[i] = window[i-1]; // se hace un shift de las muestras anteriores y se descarta la mas antigua.
	}
	window[0] = ADCread(); // se actualiza la primera muestra
	
	
	out = 0; // out opeara como acumulador, se debe hacer clear cada que se inicia un calculo del filtro.
	// calculo del filtro.
	for(int i=0; i<48 ; i++ ){
		out += window[i]*FIR[i];
	}
	
	// se pone la salida (se debe usar un DAC externo ya que este microcontrolador no dispone de este periferico.)
	PORTB = out;
}



// funcion que al ser invocada inicia convercion analogico-digital de la señal
// y devuelve su correspondiente valor.
int ADCread(){
	
	ADCSRA |= _BV(6); // se inicia la conversion.
	
	// se espera el fin de conversion.
	while( (ADCSRA&_BV(6)) ){ } // cuando la conversion finaliza el bit 6 se pone automaticamente en 0.
	_delay_ms(1);
	
	
	int low = ADCL; // se lee registro  bajo (8 bits)
	int hig = ADCH*256; // se lee registro alto (2 bits)
	
	int Radc = ADCH + ADCL //lectura del adc, ya que el MCU es de 8 bits la lectura de 10bits se parte en 2 registros.
	
	// se retorna la tension leida (se hace la conversion de bits a tension)
	return (Radc/1024)*ADC_REF;
}

