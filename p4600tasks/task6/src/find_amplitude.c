#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

//this function finds and returns the amplitude of a sin wave comprised of signed values

float find_amplitude(float* input, int length){
	float high_value = -256;
	float low_value = 256; //highest and lowest possible values of the curve

	for (int i = 0; i < length; i++)
	{
		if(input[i] > high_value) high_value = input[i];
		if(input[i] < low_value) low_value = input[i];
	}
	float amplitude = (high_value-low_value)/2;
	//printf("\n%f",high_value);
	//printf("\n%f",low_value);
	return amplitude;
}
