float get_scale(char channelNumber, ViSession* scopeHandle);

void get_curve(ViSession* handle, char channelNumber, int size, char* curveArray);

void openRM(ViSession* RM);

void setFGFrequency(ViSession* handle, int channelNumber, int frequency, int amplitude);

void error_message(char* location);