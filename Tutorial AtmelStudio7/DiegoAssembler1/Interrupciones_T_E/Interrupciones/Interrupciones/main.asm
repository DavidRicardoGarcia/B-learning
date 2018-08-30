;
; Interrupciones.asm
;
; Created: 15/07/2016 04:19:55 p.m.
; Author : dmartinez
;


;====================================================================
; DEFINICIONES INICIALES
;====================================================================     

			.EQU F_CPU	= 16000000
			.DEF TEMP 	= R16	; REGISTRO TEMPORAL
			.DEF TEMP1 	= R17	; REGISTRO TEMPORAL 1
			.DEF TEMP2	= R18	; REGISTRO TEMPORAL 2 

;====================================================================
; VECTORES DE INTERRUPCION
;====================================================================     
			
			.ORG		0x0000 
			JMP 		Inicio

			.ORG		0x0002 
			JMP 		Int_Externa0

			.ORG 		0x0028
			JMP 		InterrupcionT1	; Desbordamiento del Timer 1

;====================================================================
; PROGRAMA
;====================================================================

Inicio:

;====================================================================
; CONFIGURACIÓN DE PERIFÉRICOS : PUERTO B
;====================================================================

			LDI			TEMP,0xFF
			OUT			DDRB,TEMP						; Define el Puerto B como salida
			OUT			DDRA,TEMP						; Define el Puerto A como salida


			LDI			TEMP1,0xFF						; Inicializa el valor del puerto
			OUT			PORTB,TEMP1						; Escribe el dato almacenado en R17 en el Puerto B
						
			LDI			TEMP2,0xFF						; Inicializa el valor del puerto
			OUT			PORTA,TEMP1						; Escribe el dato almacenado en R18 en el Puerto A

;====================================================================
; CONFIGURACIÓN DE PERIFÉRICOS : TIMER 1
;====================================================================

			;CONFIGURACIÓN DEL SET TIMER
			LDI			TEMP,0x0B						; SE PRECARGA EL TIMER 1
			STS			TCNT1H,TEMP						; CON 0x0BDC=3036
			LDI			TEMP,0xDC						; VALOR NECESARIO PARA
			STS			TCNT1L,TEMP						; DESBORDAR A 1Seg

						;CONFIGURACIÓN DEL PRESCALER:
			LDI			TEMP,1<<CS12|0<<CS11|0<<CS10	; PRESCALER DE 256
			STS			TCCR1B,TEMP						; AQUÍ INICIA EL TIMER

;====================================================================
; HABILITAR INTERRUPCIONES TIMER 1 Y GLOBALES
;====================================================================	
			LDI			TEMP,1<<TOIE1		;Habilitación de INT_TIMER_1
			STS			TIMSK1,TEMP			

			LDI			TEMP,1<<INT0		; Habilitación de INT_EXT0
			STS			0x003D,TEMP			; EIMSK

			LDI			TEMP,0x01			; Selecciona activación por cualquier flanco
			STS			EICRA,TEMP			

			SEI								; Habilitador global de interrupciones

;====================================================================
; BUCLE INFINITO : LOOP
;====================================================================	

BUCLE:      NOP
			JMP			BUCLE							;BUCLE INFINITO

;====================================================================
; Subrutina de Atención a la Interrupción del Timer 1
;====================================================================	

InterrupcionT1:
	
			LDI			TEMP,0x0B			;SE VUELVE A CARGAR
			STS			TCNT1H,TEMP			;EL TEMPORIZADOR 1
			LDI			TEMP,0xDC			;CON EL VALOR DE 3036
			STS			TCNT1L,TEMP			;DEBIDO AL DESBORDAMIENTO

			COM			TEMP1				; Complemento a 1 el valor en el R16
			OUT			PORTB,TEMP1			; Escribe el dato almacenado en R16 en el Puerto B
			
			RETI

;====================================================================
; Subrutina de Atención a la Interrupción Externa 0
;====================================================================	

Int_Externa0:

			COM			TEMP2				; Complemento a 1 el valor en el R18
			OUT			PORTA,TEMP2			; Escribe el dato almacenado en R18 en el Puerto A
			
			RETI

;======================================================================
; FIN DEL PROGRAMA
;======================================================================