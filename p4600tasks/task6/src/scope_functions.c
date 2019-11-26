//This file is for wrapper functions to read/write from the scope easier.
#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <scope_functions.h>

void error_message(char* location)
{
	printf("\nCould not complete function %s",location);
	exit(EXIT_FAILURE);
}

float get_scale(char channelNumber, ViSession* scopeHandle)
{	
	ViStatus status;
	ViUInt32 resultCount;

	char request[9]; //the actual request to the scope
	char ret[20]; //what the read function returns into. Must convert into a float value.
	float scale; //where the scale will be held

	sprintf(request,"CH%d:SCA?\n",channelNumber);
	status = viWrite(*scopeHandle,request,9,&resultCount); //request the scale for the scope
	if(status != VI_SUCCESS)
	{	
		char message[9];
		sprintf(message,"get_scale");
		error_message(message);
	}
	else
	{
	viRead(*scopeHandle,ret,20,&resultCount);		//places it in a string called ret
	sscanf(ret,"%f",&scale); //converts the returned value to the scale variable
	//volts=atof(ret) //alternative way
	return scale;
	}
}

void get_curve(ViSession* handle, char channelNumber, int size, char* curveArray)
{
	ViStatus status;
	ViUInt32 resultCount;
	char request[12]; //the request to the scope
	sprintf(request,"DAT:SOU CH%d\n",channelNumber);
	status = viWrite(*handle,request,12,&resultCount);
	if(status != VI_SUCCESS)
	{
		char message[9];
		sprintf(message,"get_curve");
		error_message(message);
	}
	else
	{
	viWrite(*handle,"CURV?\n",6,&resultCount);
	_sleep(2);
	viRead(*handle,curveArray,size,&resultCount);
	}
}

//open the RM
void openRM(ViSession* defaultRM)
{
	ViStatus status;
	ViUInt32 resultCount;
	status = viOpenDefaultRM(defaultRM);
	if(status != VI_SUCCESS)
	{
	 char message[7];
	 sprintf(message,"open_RM");
	 error_message(message);
	}
}

void findScope()
{

}

void openScope()
{

}

void findFG()
{

}

void openFG()
{

}

void setFGFrequency(ViSession* handle, int channelNumber, float frequency, float amplitude)
{	
	ViStatus status;
	ViUInt32 resultCount;
	char request[64];
	printf("SOUR%d:APPL:SIN %0.2E,%0.2f\n",channelNumber,frequency,amplitude);
	sprintf(request,":SOUR%d:APPL:SIN %0.2E,%0.2f\n",channelNumber,frequency,amplitude);
	//char requestlength[10];
	//sprintf(requestlength,strlen(request));
	//printf(requestlength);
	//fflush(stdout);
	status = viWrite(*handle,request,strlen(request),&resultCount);
	if(status != VI_SUCCESS) //do I need this check?smsys
		
	{
		char message[13];
		sprintf(message,"set_frequency");
		error_message(message);
	}
	else
	{
	
	}
}

