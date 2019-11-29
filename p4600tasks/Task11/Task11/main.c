/*
 * Task11.c
 *
 * Created: 11/21/2019 10:47:09 AM
 * Author : Michael
 * Using ADC on the ATMEGA328P
 * Traffic light system
 */ 

#include <avr/io.h>

#define RED_LIGHT PD2
#define YELLOW_LIGHT PD1
#define GREEN_LIGHT PD0
void setup()
{
	//ADMUX: Choose reference source, input channel
	//ADMUX defaults to 0: ADC0 is already on
	//ADCSRA: ADEN -> Turn ADC on
	
	
	//ADPS(2->0): Sampling frequency
	//set data directions
	DDRD |= (1<<RED_LIGHT) | (1<<YELLOW_LIGHT) | (1<<GREEN_LIGHT);
	
	ADCSRA |= (1<<ADEN); //turn on ADC
	ADMUX |= (1<<MUX0);
	ADMUX |= (1<<REFS0); //sets the ADC compare mode
	
}

uint16_t get_adc_value()
{
	uint16_t lowbyte;
	uint16_t highbyte;
	
	ADCSRA |= (1<<ADSC); //ADCSRA: ADSC -> Start data acquisition
	
	while(!(ADCSRA & (1<<ADIF))); //wait for ADC to complete
	
	//ADCH and ADCL are where data ends up
	//10 bit value held in 2 8 bit registers

	lowbyte = ADCL; // 00000000 11101101
	highbyte = ADCH; // 00000000 00000010
	uint16_t finalvalue;
	finalvalue = (highbyte << 8) | lowbyte;
	//ADCSRA &= ~(1<<ADSC);
	return finalvalue;
}
int main(void)
{	
	uint16_t adc_value;
    setup();
    while (1) 
    {
		adc_value = get_adc_value();
		if(adc_value > 600)
		{
			PORTD |= (1 << GREEN_LIGHT);
			PORTD &= ~(1 << YELLOW_LIGHT);
			PORTD &= ~(1 << RED_LIGHT);
		}
		if((adc_value < 600)&&(adc_value > 300))
		{
			PORTD |= (1 << YELLOW_LIGHT);
			PORTD &= ~(1 << RED_LIGHT);
			PORTD &= ~(1 << GREEN_LIGHT);
		}
		if(adc_value < 300)
		{
			PORTD |= (1 << RED_LIGHT);
			PORTD &= ~(1 << YELLOW_LIGHT);
			PORTD &= ~(1 << GREEN_LIGHT);
		}
    }
}

