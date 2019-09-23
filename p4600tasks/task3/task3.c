#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//create a function that writes a data file consisting of the x and y data of a sin wave
int main()
{
	FILE * trig_file;

	float x[64];
	float y[64];

	trig_file = fopen("trig_data.dat","a"); // create a file for writing the data to
	int i;
	for(i = 0; i < (sizeof(x)/sizeof(x[0]));i++) //create a set of x values from 0 to 8*pi
	{
		x[i] = 3.1415*i/8;
		y[i] = sin(x[i]);
		fprintf(trig_file,"\n%f %f",x[i],y[i]);

	}

	fclose(trig_file);
	return 0;


/*
	input_file = fopen("data.dat","r"); //read mode

	if(input_file != NULL)
	{
	fscanf(input_file,"%f %f", &x, &y);
	fclose(input_file);
	}
	input_file = fopen("hello.txt","a"); //append mode
	fprintf(input_file,"Hello from x %f and y %f",x,y);
	fclose(input_file);
*/
}