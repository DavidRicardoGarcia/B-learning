;
; EjemploAssembler1.asm
;
; Created: 27/08/2018 1:18:26 p. m.
; Author : esteban
; YoutubeChannel: 
; Instagram: RoughGentleman77
; demostracion del parpadeo de un led usando lenguaje ensamblador.
; para mas informacion ver la guia en este mismo repositorio

.equ PB = 2


start:
	ldi r16, PB
	ldi r17, 0x00
	out DDRB, r16 ; se establece el pin 1 como salida digital.
	nop
	out PORTB, r16 ; se pone el pin 1  del puerto B en nivel logico alto.
	nop

	; el retardo se implementa contando hasta 1048576 usando 3 registros de 8 bits.
	; se debe tener en cuenta que las instrucciones para incrementar, clarear registros y comparaciones tambien intervienen en el retardo
	; por tanto el retardo logrado es mayor a 1048576 ciclos de maquina.

	eor r18, r18 ; or exclusiva A xor A = 0. esta instruccion hace clear del registro r19 (proposito general).
	eor r19, r19 
	eor r20, r20
loop: 
	inc  r18 ; incrementa +1 al valor del registro r18
	cpi r18, 0xff ; se compara r18 con 255
	brlo loop ; si en la comparacion da r18 menor a 255 se regresa el program counter a loop:

	eor r18, r18 ; cuando r18 ya no es menor a 0xff (255) entonces se pone r18 nuevamente en 0
	inc r19 ; se incrementa r19 con +1
	cpi r19, 0xff ; se compara r19 con 255
	brlo loop ; se regresa el program counter a loop

	eor r19, r19 ; se hace clear de r19
	inc r20
	cpi r20, 0x10 ; se compara r20 con 16
	brlo loop ; se regresa el program counter a loop si r20 < 16

	out 0x18, r17 ; se pone la salida en 0


	; esta es un copy and paste de la porcion de codigo para hacer el retardo
	eor r18, r18 
	eor r19, r19 
	eor r20, r20
loop2: 
	inc  r18 
	cpi r18, 0xff 
	brlo loop2

	eor r18, r18
	inc r19 
	cpi r19, 0xff
	brlo loop2 

	eor r19, r19 
	inc r20
	cpi r20, 0x10 
	brlo loop2 


    rjmp start ; salta a la primera instruccion

	; se define una rutina de delay