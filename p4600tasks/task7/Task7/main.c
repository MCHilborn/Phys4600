/*
 * Task7.c
 *
 * Created: 11/4/2019 6:23:12 PM
 * Author : Michael
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void loop()
{
	PORTD |= (1<<PD1);
	_delay_ms(100);
	PORTD &= ~(1<<PD1);
	_delay_ms(100);
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		loop();
    }
}

