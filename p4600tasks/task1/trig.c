#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float fAngle;
	float fHypot = 12;
	float fOpp;

	for(fAngle = 0; fAngle < M_PI / 2; fAngle+= M_PI / 20)
	{


		fOpp = fHypot * sin(fAngle);

		printf("Opposite side = %f cm\n", fOpp);
	}


	return 0;
}