#include "sdk/agenttime.h"

#include "util/NTPClient.h"

time_t get_time(time_t* currentTime)
{
    NTPClient ntpClient;
    uint32_t epochTime;

    ntpClient.begin();
    epochTime = ntpClient.getEpochTime("time.nist.gov");
    ntpClient.end();

    if (currentTime) {
        *currentTime = epochTime;
    }

    return epochTime;
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
