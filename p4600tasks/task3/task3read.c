//This file will use the sin-wave data
//it will calculate the mean and standard deviation of the y column
//it will work with files of different lengths
//user will be able to enter the file name atd the command line
//program should give useful error messages

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float findMean(float* input, int len){ //returns the mean of the entered array
	float sum = 0;
	float mean = 0;
	for (int i = 0; i < len; i++){
		sum+=input[i];
	}
	mean = sum/len;
	printf("\nMean = %f",mean);

	return mean;
}

float findStdDev(float* input, float mean, int len){ //returns the standard deviation of the entered array
	float sum;
	for (int i = 0; i < len; i++){
		sum+=powf((input[i]-mean),2);
	}
	float stdDev = sqrt(sum/(len-1));
	printf("\nStandard Deviation = %f",stdDev);

	return stdDev;
}


int main(){
	FILE* dataFile;
	char filename[10];
	int counter = 0;
	float x;
	float z;


	printf("\nEnter the name of the file with the data: "); //user must enter filename of data
	scanf("%s",filename); //filename is head in variable filename
	//printf("\n%s",filename);
	dataFile = fopen(filename,"r");
	if(dataFile != NULL){
		while(fscanf(dataFile,"%f %f",&x,&z)!= EOF){ //just counting how many rows are in the file
			counter++;
		}
		float y[counter]; //create an array with the same number of elements as there are lines of data
		rewind(dataFile); //have to do this to get to beginning of file

		for (int i = 0; i < counter; i++){
			fscanf(dataFile,"%f %f",&x,&y[i]);
		}
		float mean = findMean(y,counter);
		float stdDev = findStdDev(y,mean,counter);



	}
	else printf("\nCouldn't read file called: %s",filename);

	//dataFile = fopen()
}
