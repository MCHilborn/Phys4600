#include <stdio.h>
#include <stdlib.h>
#include <math.h>	
#include <visa.h>
#include "find_amplitude.h"
#include "smoothing_function.h"

void main(int argc, char** argv)
{
	unsigned char resultBuffer[256];
	ViStatus status = VI_SUCCESS;
	ViFindList resourceList;
	ViUInt32 num_inst;
	ViUInt32 resultCount;

	ViSession defaultRM, scopeHandle;
	ViChar description[VI_FIND_BUFLEN];
	char dataBuffer[2500];

	int y;

	int lsb;
	int msb;

	status = viOpenDefaultRM(&defaultRM);

	if(status == VI_SUCCESS)
	{
		status = viFindRsrc(defaultRM,"USB[0-9]::?*INSTR",	&resourceList,&num_inst,description);
		if(status == VI_SUCCESS)
		{
			status = viOpen(defaultRM,description,	VI_NULL,VI_NULL,&scopeHandle);

			if(status == VI_SUCCESS)
			{
				printf("\nOpened %s\n",description);

				viWrite(scopeHandle,"WFMP?\n",6,&resultCount);
				viRead(scopeHandle,resultBuffer,256,&resultCount);


				viWrite(scopeHandle,"DAT:STOP 2500\n",14,&resultCount);

				printf("\nResult count = %d",resultCount);
				printf("\nResult buffer = %s\n",resultBuffer );


				char ret[20]; //character array the scale will be returned to
				ret[19] = '\0';
				viWrite(scopeHandle,"CH1:SCA?\n",9,&resultCount); //request the scale for the scope
				viRead(scopeHandle,ret,20,&resultCount);	
				printf("Scale is %s\n", ret);

				//turn the string into a floating point number
				//sscanf takes string and turns it into a number
				float volts;
				sscanf(ret,"%f",&volts);
				//volts=atof(ret) //alternative way
				printf("\n volts: %f",volts);

				//conversion factor
				float conversionFactor = 10.0*volts/256; //10 divisions on the screen
				viWrite(scopeHandle,"DAT:SOU CH1\n",12,&resultCount);
				viWrite(scopeHandle,"CURV?\n",6,&resultCount);
				_sleep(2);
				viRead(scopeHandle,dataBuffer,2500,&resultCount); //returns a signed integer




				float floatBuffer[2500];
				for (int j = 0; j < 2500; j++)
				{
					//if(j<500) printf("\n%d ",dataBuffer[j]);

					floatBuffer[j] = dataBuffer[j]*conversionFactor;
				}

				//smooth the curve
				float smoothedArray[2300]; //this has to be smaller than the total array size due to windowing effects
				smooth_array(floatBuffer,smoothedArray,2300); //this makes a smoothed array from floatBuffer and puts it in smoothed_array
				//for (int k = 2290; k< 2300; k++) printf("\n%f", smoothedArray[k]);

				float amplitude = find_amplitude(smoothedArray,2300);
				printf("\n Amplitude = %f",amplitude);

					/*for(int i = 0; i<128; i++)
				{
					y = dataBuffer[i];
					printf("\nRaw = %x,  Read = %f",y,floatBuffer[i]);
				}*/

				//convert amplitude to a voltage

				printf("\nconversion factor: %f",conversionFactor);
				printf("\n Amplitude = %f", amplitude);
					
				
			
			}
			else
			{
				printf("\nFailed to open %s",description);
			}
		}
		else
		{
			printf("\nCouldn't find any instruments");
		}
	}
	else
	{
		printf("\nFailed to open defaultRM");
	}
}