#ifndef __SCOPE_FUNCTIONS_H
#define __SCOPE_FUNCTIONS_H

float get_scale(char channelNumber, ViSession* scopeHandle);

void get_curve(ViSession* handle, char channelNumber, int size, char* curveArray);

void openRM(ViSession* RM);

void setFGFrequency(ViSession* handle, int channelNumber, float frequency, float amplitude);

void error_message(char* location);

#endif