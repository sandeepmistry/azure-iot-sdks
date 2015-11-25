#include <WiFi101.h>

#include "sdk/agenttime.h"

time_t get_time(time_t* currentTime)
{
    if (currentTime == NULL) {
        return WiFi.getSystemTime();
    } else {
        return time(currentTime);
    }
}

double get_difftime(time_t stopTime, time_t startTime)
{
    return difftime(stopTime, startTime);
}

struct tm* get_gmtime(time_t* currentTime)
{
    return localtime(currentTime);
}

char* get_ctime(time_t* timeToGet)
{
    return ctime(timeToGet);
}
