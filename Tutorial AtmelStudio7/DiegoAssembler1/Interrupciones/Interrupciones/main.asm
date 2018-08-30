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

;====================================================================
; PROGRAMA
;====================================================================

Inicio:

;====================================================================
; CONFIGURACIÓN DE PERIFÉRICOS : PUERTO B
;====================================================================

			LDI			TEMP,0x01
			OUT			DDRA,TEMP						; Define el Puerto A como salida


			LDI			TEMP2,0x01						; Inicializa el valor del puerto
			OUT			PORTA,TEMP1						; Escribe el dato almacenado en R18 en el Puerto A

;====================================================================
; HABILITAR INTERRUPCIONES TIMER 1 Y GLOBALES
;====================================================================	

			LDI			TEMP,1<<INT0		; Habilitación de INT_EXT0
			STS			0x003D,TEMP			; EIMSK

			LDI			TEMP,0x02			; Selecciona activación por cualquier flanco
			STS			EICRA,TEMP			

			SEI								; Habilitador global de interrupciones

;====================================================================
; BUCLE INFINITO : LOOP
;====================================================================	

BUCLE:      NOP
			JMP			BUCLE							;BUCLE INFINITO

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