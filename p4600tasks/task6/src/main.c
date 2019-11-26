#include <stdio.h>
#include <stdlib.h>
#include <math.h>	
#include <visa.h>
#include "find_amplitude.h"
#include "scope_functions.h"
#include "smoothing_function.h"

/*This program is going to connect to the tektronix scope and the rigol signal generator
It is going to step through frequencies and read the oscilliscope curve
it will find the amplitude of the curve and store that value for that frequency
the final output will be a frequency vs amplitude graph*/

float find_bandwidth(float resistance, float capacitance, float inductance)
{
	float quality_factor = (1/resistance)*sqrt(inductance/capacitance);
	float resonant_frequency = 1/(2*M_PI*sqrt(inductance*capacitance));
	float bandwidth = resonant_frequency/quality_factor;
	return bandwidth;
}

void main()
{
	float min_frequency; //minimum and maximum frequencies this program will sweep through on the LRC circuit
	float max_frequency;

	ViStatus status = VI_SUCCESS;
	ViFindList resourceList;
	ViUInt32 num_inst;
	ViUInt32 resultCount;

	ViSession defaultRM, scopeHandle, FGHandle;
	ViChar description[VI_FIND_BUFLEN];
	char dataBuffer[2500]; //hold the active sample, dump it, and replace it
	float floatBuffer[2500];
	char message[15]; //make sure your messages aren't bigger than 15 characters.
	float resistance = 100E3;
	float capacitance = 200E-9;
	float inductance = 10E-3;
	//float bandwidth = find_bandwidth(resistance, capacitance, inductance);
	float f0 = 3E2; //initial frequency
	float frequency;
	float x_values[25];
	float y_values[25];

	FILE * output_file;
	output_file = fopen("wave_data.DAT","w");

	status = viOpenDefaultRM(&defaultRM); //open the resource manager
	if (status != VI_SUCCESS)
	{
		sprintf(message,"open_RM");
		error_message(message);
	}
	else
	{	printf("\nOpened RM");
		fflush(stdout);
		status = viFindRsrc(defaultRM,"USB[0-9]::0x0699?*INSTR",&resourceList,&num_inst,description); //find the scope
		if (status != VI_SUCCESS)
		{
			sprintf(message,"FIND_SCOPE");
			error_message(message);
		}
		else
		{	printf("\nFound Scope");
			fflush(stdout);
			status = viOpen(defaultRM,description,VI_NULL,VI_NULL,&scopeHandle); //open the scope and give it a handle
			if(status != VI_SUCCESS)
			{
				sprintf(message,"OPEN_SCOPE");
				error_message(message);
			}
			else
			{	printf("\nOpened Scope");
				fflush(stdout);
				status = viFindRsrc(defaultRM,"USB[0-9]::0x1AB1?*INSTR",&resourceList,&num_inst,description); //find the function generator
				if(status != VI_SUCCESS)
				{
					sprintf(message,"FIND_FG");
					error_message(message);
				}
				else
				{	printf("\nFound FG");
					fflush(stdout);
					status = viOpen(defaultRM,description,VI_NULL,VI_NULL,&FGHandle); //open the function generator and give it a handle
					if(status != VI_SUCCESS)
					{
						sprintf(message,"OPEN_FG");
						error_message(message);
					}
					else
					{ printf("\nOpened FG");
					  fflush(stdout);
					//both the  scope and the FG have been found and opened

					/*now set the function generator to the base frequency.
					Take the amplitude of the resulting wave
					create a set of data that shows the amplitudes at various frequencies*/
					//going to take 10 points of data only
					float conversion_factor = 10*get_scale(1,&scopeHandle)/256; //find the conversion factor to turn the value into voltages
					for (int i = 0; i < 15; i++)
					{	
						frequency = f0+i*f0; //frequency we will find amplitude at
						x_values[i] = frequency;
						setFGFrequency(&FGHandle,1,frequency,5); //set the function generator @5V to the frequency;
						get_curve(&scopeHandle,1,2500,dataBuffer); //read the scope connected and put the data into the dataBuffer
						//TODO: Put curve data into a text file

						//have to convert the values in the dataBuffer into float values. Also scale them into voltages
						for(int j = 0; j < 2500;j++)
						{
							floatBuffer[j] = dataBuffer[j] * conversion_factor;	
						}
						y_values[i] = find_amplitude(floatBuffer,2500); //find the amplitude and put it in the corresponding y value
						fprintf(output_file,"\n %f %f",x_values[i],y_values[i]); //might not work
					}
					printf("\ndone");
					fflush(stdout);

					}

				}
			}
		}

	}

}