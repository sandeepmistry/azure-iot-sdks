#include <WiFi101.h>
#include <WiFiUdp.h>

#ifndef NTPCLIENT_H
#define NTPCLIENT_H

#define NTP_PACKET_SIZE     48
#define NTP_PORT            123

#define DEFAULT_NTP_TIMEOUT 1000

class NTPClient
{
    public:
        NTPClient();
        int begin(const char* host = "time.nist.gov", int port = NTP_PORT);
        uint32_t getEpochTime(int timeout = DEFAULT_NTP_TIMEOUT);
        void end();

    private:
        void prepareRequest();
        void sendRequest();
        int receiveResponse(int timeout);
        uint32_t parseResponse();


        const char* _host;
        int         _port;
        char        _buffer[NTP_PACKET_SIZE];
        WiFiUDP     _udp;
};

#endif
