#include <stdlib.h>	/* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>	/* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>	/* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 


float mean_calc(float* input,int length)
{
  float mean; //holds the mean value of the array
  float sum = 0; //start the sum of all elements at 0 
  int i; //counter for the loop around each element of the array
  
  for(i = 0; i < length; i++) //may be problematic and loop to input_size-1
    {
      sum += *input; //add the value held at the current position in input 
      input++;
    }
  
  mean = sum/length;
  
  return mean;
}

float std_calc(float* input, int length, float mean)
{
  float std_dev; //holds the standard deviation
  float difference; //holds difference between value and mean
  int i;
  for(i = 0; i < length; i++)
    {
      difference+=pow((input[i] - mean),2);
    }
  return sqrt(difference/(length-1));
  
}

float mean_and_stddev(float* input, int length)
{
  //goal: try and calculate both mean and stdev with one loop of the data
  int i;
  float mean;
  float std_dev;
  float temp;
  float sum = 0;
  float square_sum = 0;
  for (i = 0; i < length; i++)
    {
      temp=input[i];
      sum+=temp;
      square_sum+=pow(temp,2); 
    }
  mean = (sum/length);
  std_dev = sqrt((square_sum-2*length*sum*mean+length*pow(mean,2)/(length-1)));
  printf("\nmean is %f", mean);
  printf("\nstandard deviation is %f", std_dev);
		 
}


int main()
{
	float data [] ={0.068038, 0.173967, 0.439303, 0.615258, 0.789436, 0.770980, 0.890924, 1.034431, 0.955555, 0.991579, 0.919359, 0.857244, 0.680064, 0.558250, 0.473129, 0.278329, 0.027142, -0.151631, -0.454363, -0.534177, -0.803847, -0.882892, -0.996433, -0.919950, -1.068664, -1.000596, -0.997921, -0.909708, -0.607322, -0.611919, -0.380097, -0.127268};

	float mean;
	float std_dev;
	/*  ==== START OF YOUR CODE ==== */

	int data_size  = (sizeof(data)/sizeof(data[0])); //determine size of the array by finding the size of the input
	mean = mean_calc(data,data_size);
	std_dev = std_calc(data, data_size, mean);
	mean_and_stddev(data,data_size);

	/*  ==== END OF YOUR CODE ==== */
	

	/* These lines will output the results to console */
	printf("\nMean = %f", mean);
	printf("\nStandard deviation = %f", std_dev);

	
	return 0;  // Functions which return a value MUST contain at least one return statement
} 
