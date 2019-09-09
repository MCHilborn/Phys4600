#include <stdlib.h>	/* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>	/* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>	/* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 


int main()
{
	float data [] ={0.068038, 0.173967, 0.439303, 0.615258, 0.789436, 0.770980, 0.890924, 1.034431, 0.955555, 0.991579, 0.919359, 0.857244, 0.680064, 0.558250, 0.473129, 0.278329, 0.027142, -0.151631, -0.454363, -0.534177, -0.803847, -0.882892, -0.996433, -0.919950, -1.068664, -1.000596, -0.997921, -0.909708, -0.607322, -0.611919, -0.380097, -0.127268};

	float mean;
	float std_dev;

	/*	Here you can put the code to find the standard deviation of the data array	*/


	/*  ==== START OF YOUR CODE ==== */

	/*calculating mean*/

	/*first get the number of elements in the array*/
	int array_size = (sizeof(data)/sizeof(data[0]));
	/*next calculate the mean by iterating through, counting the total, and dividing by the size*/
	float sum;
	int i;
	for (i = 0; i < array_size; i++)
	{
		sum += data[i];
	}
	mean = sum/array_size;

	/*now for the stdev*/
	int j;
	/*find the variance*/
	float variance = 0;
	for (j=0; j < array_size; j++)
	{
		variance += pow((data[j] - mean),2);
	}

	/*calculate standard deviation*/
	std_dev = sqrt(variance/array_size);


	/*  ==== END OF YOUR CODE ==== */


	/* These lines will output the results to console */
	printf("\nArraySize = %i",array_size);
	printf("\nMean = %f", mean);
	printf("\nStandard deviation = %f", std_dev);

	
	return 0;  // Functions which return a value MUST contain at least one return statement
}