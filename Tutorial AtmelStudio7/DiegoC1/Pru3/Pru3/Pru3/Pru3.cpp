/*
 * Pru3.cpp
 *
 * Created: 18/07/2016 04:19:07 p.m.
 * Author : dmartinez
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>


char Sacar_Dato(char dato);


int valor = 255;
int pru2;
char x;

float seno[1001]={350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000,390.5666,429.5087,465.3000,496.6053,522.3599,541.8338,554.6735,560.9211,561.0080,555.7248,546.1685,533.6701,519.7088,505.8159,493.4757,484.0307,478.5940,477.9780,482.6414,492.6585,507.7130,527.1171,549.8533,574.6377,600.0000,624.3757,646.2040,664.0265,676.5786,682.8698,682.2468,674.4355,659.5594,638.1333,611.0328,579.4408,544.7755,508.6035,472.5435,438.1678,406.9054,379.9557,358.2161,342.2285,332.1486,327.7397,328.3906,333.1579,340.8286,350.0000,359.1714,366.8421,371.6094,372.2603,367.8514,357.7715,341.7839,320.0443,293.0946,261.8322,227.4565,191.3965,155.2245,120.5592,88.9672,61.8667,40.4406,25.5645,17.7532,17.1302,23.4214,35.9735,53.7960,75.6243,100.0000,125.3623,150.1467,172.8829,192.2870,207.3415,217.3586,222.0220,221.4060,215.9693,206.5243,194.1841,180.2912,166.3299,153.8315,144.2752,138.9920,139.0789,145.3265,158.1662,177.6401,203.3947,234.7000,270.4913,309.4334,350.0000};
float sen1[1001];

int main(void){

	int pru1, i=0;
	
	DDRA  = 0xFF;            			//PORTB como salida
	PORTA = 0X00;            			//Inicia PORTB en 0
	
		
	DDRB  = 0xFF;            			//PORTB como salida
	PORTB = 0X00;            			//Inicia PORTB en 0

	 //TIMER1
	 
	 asm("LDI R16,1<<2|0<<1|0<<0	; PRESCALER DE 256");
	 asm("STS 0x81,R16				; AQU� INICIA EL TIMER");	// 0x81 = TCCR1B
	 asm("LDI R16,0x0B				; SE PRECARGA EL TIMER 1");
	 asm("STS 0x85,R16				; CON 0x0BDC=3036");		// 0x85 = TCNT1H
	 asm("LDI R16,0xDC				; VALOR NECESARIO PARA");
	 asm("STS 0x84,R16				; DESBORDAR A 1 Seg");		// 0x84 = TCNT1L
	 asm("LDI R16,1<<0				; HABILITACI�N DE INT");
	 asm("STS 0x6F,R16				; DE TIMER 1");				// 0x6F = TIMSK1
	 
	 sei();											// Interrupciones Globales


	
	while (1) {

	pru1 = valor+1;
	pru2 = valor+2;
	x = char (pru1);
	PORTA = pru1;

	sen1[i] = seno[i]+1;
	i++;
	
	asm("NOP");

	}
	
}


ISR(TIMER1_OVF_vect){	// Subrutina de atenci�n a la interrupci�n del Timer 1
	
	 asm("LDI R16,0x0B		; SE PRECARGA EL TIMER 1");
	 asm("STS 0x85,R16		; CON 0x0BDC=3036");		// 0x85 = TCNT1H
	 asm("LDI R16,0xDC		; VALOR NECESARIO PARA");
	 asm("STS 0x84,R16		; DESBORDAR A 1 Seg");		// 0x84 = TCNT1L

	valor = Sacar_Dato(valor);
	
}


char Sacar_Dato(char dato){
	
	dato = ~dato;
	PORTB = dato;

	return(dato);
	
}

