//This file is for wrapper functions to read/write from the scope easier.

void get_scale(char* ret)
{
	viWrite(scopeHandle,"CH1:SCA?\n",9,&resultCount); //request the scale for the scope
	viRead(scopeHandle,ret,20,&resultCount);		//places it in a string called ret
}

void get_curve_ch1(ViSession handle, char* curveArray)
{
	viWrite(handle,"DAT:SOU CH1\n",12,&resultCount);
	viWrite(handle,"CURV?\n",6,&resultCount);
	_sleep(2);
	viRead(handle,curveArray,2500,&resultCount); //returns a signed integer
}

void get_curve_ch2(ViSession handle, char* curveArray)
{
	viWrite(handle,"DAT:SOU CH2\n",12,&resultCount);
	viWrite(handle,"CURV?\n",6,&resultCount);
	_sleep(2);
	viRead(handle,curveArray,2500,&resultCount); //returns a signed integer
}

//open the scope
void openRM()
{
	ViStatus status = VI_SUCCESS;
	ViSession defaultRM;
	status = viOpenDefaultRM(&defaultRM);
	if(status != VI_SUCCESS)
	{
	 printf("\nCould not open defaultRM");
	}
	
}