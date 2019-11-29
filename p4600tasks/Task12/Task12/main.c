/*
 * Task12.c
 *
 * Created: 11/25/2019 10:59:08 AM
 * Author : Michael
 */ 
//send numbers from 1 to 128 to the shift register

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


#define MOSI PB3
#define SCK PB5
#define CS PB6
#define SS PB2 //keep high

void setup()
{
	SPCR |= (1<<SPE); //enable SPI
	SPCR |= (1<<MSTR); //master
	SPCR |= (1<<CPOL); //clock polarity
	DDRB |= (1<<MOSI) | (1<<SCK) | (1<<CS) | (1<<SS);
	
}

void function(uint8_t data)
{
	
	uint8_t datarecieved;
	
	PORTB &= ~(1<<CS); //pulls CS low
	SPDR = data; //starts the clock and starts trying to transmit
	
	while(!(SPSR & (1<<SPIF)));
	
	datarecieved = SPDR;
	
	PORTB |= (1<<CS); //sets CS line high again
	
}
int main(void)
{
    /* Replace with your application code */
	setup();
    while (1) 
    {	
		uint8_t i = 0;
		while(i < 127)
		{
			_delay_ms(500);
			function(i);
			i+=1;
		}
    }
}

