#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//this function produces a noisy sin wave, for smoothing later

void main(){
  FILE* sin_output;
  int sin_wave_size = 500;
  float sin_wave[sin_wave_size]; //make an 1000 point sin wave
  float x[sin_wave_size]; //x values for calculating sin wave

  sin_output=fopen("noisy_sin_wave.DAT","w");
  if(sin_output != NULL){
  for (int i = 0; i < sin_wave_size; i++){
    x[i]=M_PI*i/64;
    float rand1=(float)rand()/(float)RAND_MAX;
    float rand2=(float)rand()/(float)RAND_MAX;
    sin_wave[i]=sin(x[i])+((rand1-rand2)/10); //add noise between -.1 and .1
    fprintf(sin_output,"\n%f %f",x[i],sin_wave[i]);
  }
  fclose(sin_output);
  }
  else printf("\nCould not open file"); 
  //this part will print the values to two separate files so I can check it
  /*FILE* x_output;
  FILE* y_output;
  y_output = fopen("y_output.DAT","w");
  x_output = fopen("x_output.DAT","w");
  if(y_output!=NULL && x_output != NULL){
    for(int j = 0; j < sin_wave_size;j++){
      fprintf(x_output,"\n%f",x[j]);
      fprintf(y_output,"\n%f",sin_wave[j]);
    }
  fclose(x_output);
  fclose(y_output);
  }

  else printf("\nCould not open file"); */
  

}
