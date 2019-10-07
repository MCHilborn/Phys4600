#include <stdio.h>
#include <stdlib.h>
#include <math.h>	
#include <visa.h>
#include "find_amplitude.h"

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


				viWrite(scopeHandle,"DAT:STOP 250\n",13,&resultCount);

				printf("\nResult count = %d",resultCount);
				printf("\nResult buffer = %s\n",resultBuffer );

				viWrite(scopeHandle,"DAT:SOU CH1\n",12,&resultCount);
				viWrite(scopeHandle,"CURV?\n",6,&resultCount);
				sleep(2);
				viRead(scopeHandle,dataBuffer,250,&resultCount);

				float floatBuffer[250];
				for (int j = 0; j < 250; j++)
				{

					floatBuffer[j] = dataBuffer[j];
				}

				float amplitude = find_amplitude(floatBuffer,250);
				printf("\n Amplitude = %f",amplitude);

				for(int i = 0; i<128; i++)
				{
					y = floatBuffer[i];
					printf("\nRaw = %x,  Read = %f",y,y);
				}
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