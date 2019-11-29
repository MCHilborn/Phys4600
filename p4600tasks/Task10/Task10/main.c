/*
 * Task10.c
 *
 * Created: 11/18/2019 6:28:51 PM
 * Author : Michael
 */ 
//next task: Switch to phase correct PWM

#include <avr/io.h>

void setup()
{
	DDRD |= (1<<PD6); //set as output, special pin that works with TCCR0A
	DDRD |= (1<<PD5); //OC0B pin
	
	TCCR0A |= (1<<COM0A0) | (1<<COM0A1); //hardware interrupt
	TCCR0A |= (1<<COM0B0) | (1<<COM0B1);
	
	TCCR0B = 0x01; //sets CS00 to 1, sets no prescaler
	
	//set fast PWM mode
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	//TCCR0B |= (1<<WGM00); //| (1<<WGM00); //| (1<<CS00);
	
	OCR0A = 200; //comparison value
	OCR0B = 100;
}

void loop()
{
	
}
int main(void)
{
	setup();
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

