#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

//this function finds and returns the amplitude of a sin wave

float find_amplitude(float* input, int length){
	float high_value = 0;
	float low_value = 0; //highest and lowest values of the curve

	for (int i = 0; i < length; i++){
		if(input[i] > high_value) high_value = input[i];
		if(input[i] < low_value) low_value = input[i];
	}
	float amplitude = (high_value-low_value)/2;
	return amplitude;
}
