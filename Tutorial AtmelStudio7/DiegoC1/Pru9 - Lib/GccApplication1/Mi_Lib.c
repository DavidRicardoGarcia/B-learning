

char Sacar_Dato(char dato);



char Sacar_Dato(char dato){
	
	dato = ~dato;
	PORTB = dato;

	return(dato);
	
}
