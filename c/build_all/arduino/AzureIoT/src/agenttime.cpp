#include <WiFi101.h>
#include <WiFiUdp.h>

#include "sdk/agenttime.h"

const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];

time_t get_time(time_t* currentTime)
{
    WiFiUDP ntpUdp;

    ntpUdp.begin(2390);

    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12]  = 49;
    packetBuffer[13]  = 0x4E;
    packetBuffer[14]  = 49;
    packetBuffer[15]  = 52;

    ntpUdp.beginPacket("time.nist.gov", 123);

    ntpUdp.write(packetBuffer, NTP_PACKET_SIZE);

    delay(1000);

    while(!ntpUdp.parsePacket());

    ntpUdp.read(packetBuffer, NTP_PACKET_SIZE);


    uint32_t epoch = (word(packetBuffer[40], packetBuffer[41]) << 16 | word(packetBuffer[42], packetBuffer[43])) - 2208988800UL;

    Serial.println(epoch);
    Serial.flush();

    if (currentTime) {
        *currentTime = epoch;
    }

    return epoch;
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
