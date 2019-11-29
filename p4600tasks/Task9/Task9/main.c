/*
 * Task9.c
 *
 * Created: 11/14/2019 6:36:25 PM
 * Author : Michael
 */ 
//This project will turn an LED on and off using interrupts
//new detail: add an interrupt to change the duty cycle of the square wave
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER0_OVF_vect) //interrupt service register
{
	PORTD^= (1 << PD1);
}

ISR(TIMER0_COMPA_vect)
{
	PORTD^= (1 << PD1);
}

void loop()
{	
	
}

void setup()
{
	DDRD |= (1 << PD1); //set as output
	PORTD &= ~(1 << PD1); //initialize as 0 (off)
	
	TCCR0B = 0x01; //set as hex 1 (normal counting mode, no prescaler)
	//TIMSK0 = 1; //enables interupt when timer overflows
	
	//TIMSK0 = 3; //enables interrupt for timer overflow and OCROA 3 = 0000011;
	TIMSK0 |= (1 << OCIE0A) | (1 << TOIE0);
	
	OCR0A = 200; //triggers interrupt at 200 count for the timer
	
	sei();
	
}
int main(void)
{
    /* Replace with your application code */
	setup();
    while (1) 
    {
		loop();
    }
}

