#include <stdio.h>
#include <math.h>

void smooth_array(float* data, float* output, int length){
  
  int window_size = 5;
  //only odd lengthed windows
  
  float smoothed_array_size=(length-(window_size-1)); //filtering reduces the size of the final array
  //float smoothed_array[smoothed_array_size]; //holds final smoothed array
  float temp_value = 0;//temporary values from the window that are summed and added to the final array
  float temp_sum = 0;//sum of the values in the window that is added to the final array
  
  for(int i = 0; i < smoothed_array_size; i++){//iterate through my data up to as many points as I can fit in my smoothed curve
    temp_sum = 0;//start temporary sum at 0
    for (int j = 0; j < window_size; j++){ //build a window from a number of elements in the array
      temp_value=(float)(data[i+j]/window_size); //scale each element
      temp_sum+=temp_value; //add the scaled elements to make an average
    }
    output[i]=temp_sum;
  }
}
