#include <stdio.h>
#include "smoothing_function.h"
#include "find_amplitude.h"

void main(){
	FILE* noisy_wave_file; //this is my input file
	noisy_wave_file = fopen("noisy_sin_wave.DAT","r");
	//smooth the noisy wave
	float temp_x;
	float temp_y;
	int counter=0; //to find number of elements in the noisy wave

	if(noisy_wave_file != NULL){ //this is reading all the lines in the file to determine the size
		while(fscanf(noisy_wave_file,"%f %f",&temp_x,&temp_y)!= EOF){
			counter++;
		}

	float noisy_wave[counter]; //make an array that holds all the y values
	rewind(noisy_wave_file);

		for(int i = 0; i < counter; i++){ // this is reading the lines and placing them into x and y values
			fscanf(noisy_wave_file,"%f %f", &temp_x, &noisy_wave[i]); //do I need &?
		}


		//test to see if the data is going into the noisy wave array
		/*for(int k = 0; k < 100; k++){
			printf("%f\n",noisy_wave[k]);
		}*/
		
	float smoothed_wave[counter]; //this holds the y values of the wave after filtering
	smooth_array(noisy_wave, smoothed_wave, counter); //run the smoothing function


	/*	for(int j = 0; j < 100; j++){ //test by printing out some values
			printf("%f\n",smoothed_wave[j]);
		}
	
	}*/

	//output my smoothed wave to a file so I can plot it
	FILE* smoothed_output_file;
	smoothed_output_file = fopen("Smoothed_data.DAT","w");
	for(int j = 0; j < counter; j++){
		fprintf(smoothed_output_file,"\n%f",smoothed_wave[j]);
	}

	fclose(noisy_wave_file);
	fclose(smoothed_output_file);
	//now to use the amplitude function
	float amplitude = 0;
	amplitude = find_amplitude(smoothed_wave, counter);
	printf("\nAmplitude is: %f",amplitude);
	}
	else printf("\nCould not find file");


	
	
}