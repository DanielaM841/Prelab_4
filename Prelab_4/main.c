/*
 * Prelab_4.c
 *
 * Created: 4/04/2025 02:28:29
 * Author : Daniela Moreira
 *Descripción: Contador de 8 bits para Prelab 4
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

/******** Variables***********/
uint8_t bandera=0;
uint8_t contador = 0;

/***************************/
// Function prototypes
void setup();
void botones();


int main(void)
{
    /* Replace with your application code */
	setup();
    while (1) 
    {
		botones();
    }
}
//NON_Interrupt subroutines 
void setup()
{
	cli();
	DDRD = 0xFF; //COnfigurar el PORTD como salidas 
	PORTD = 0x00; //inicialmente apagado 
	DDRC = 0x00; // configurar el pin c como entrada
	PORTC |= (1<<PORTC0) | (1<<PORTC1); //Activar los pull-ups en el bit 0 y 1 
	DDRB |=  (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4); //pines para los transistores 
	PORTB = 0x00; //inicialmente apagado
	//habilitar interrupciones de pinchange 
	PCICR |= (1 << PCIE1);		//habilita interrupciones en el PORTC
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9);	//interrupciones para PC0 y PC1
	sei(); 
}
void botones()
{
	switch (bandera){
		case 1:
		contador++; //Incrementar contador
		PORTD=contador;		//mostrar en el puerto
		bandera=0;				//Resetear variable
		break;
		
		case 2:
		contador--;			//Decrementar contador
		PORTD=contador;
		bandera=0;				//Resetear pb
		break;
		
		default:
		break;
	}
}
//ISR
ISR(PCINT1_vect)
{
	// Verificamos si PC0 está presionado (nivel bajo)
	if (!(PINC & (1 << PINC0)))
	{
		bandera = 1; // Botón para incrementar
	}
	else if (!(PINC & (1 << PINC1)))
	{
		bandera = 2; // Botón para decrementar
	}
}

