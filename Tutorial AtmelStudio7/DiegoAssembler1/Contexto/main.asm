;
; Contexto.asm
;
; Created: 12/09/2016 04:04:41 p.m.
; Author : dmartinez
;

			.DEF TEMP 	= R16	;REGISTRO TEMPORAL
			.DEF TEMP1 	= R17	;REGISTRO TEMPORAL1

;			sensores		=> 	PORTA	; Tiene conectado todos los sensores
;			visualizador	=> 	PORTB	; visualiza el estado de los sensores
;			actuadores		=> 	PORTC	; Tiene conectado todos los actuadores

			LDI		TEMP1,0x00
			OUT		DDRA,TEMP1

			LDI		TEMP1,0xFF
			OUT		DDRB,TEMP1

			LDI		TEMP1,0xFF
			OUT		DDRC,TEMP1

inicio:		IN		TEMP,PINA			; Lee el estado de los sensores
			CALL	visualizar			; Muestra el estado de los sensores
			SBRS	TEMP,0				; Salta a apagar	
			JMP		prender		
apagar:		CBI		PORTC,0				; Si el sensor del bit0 está encendido
			JMP		inicio				; apaga el actuador bit 0
prender:	SBI		PORTC,0				; Si el sensor del bit0 está apagado
			JMP		inicio				; enciende el actuador bit 0

visualizar:	PUSH	TEMP
			OUT		PORTB,TEMP
			LDI		TEMP,0x0
			POP		TEMP
			RET

