#include <WiFi101.h>

#include "sdk/httpapi.h"

#define HTTP_API_DEBUG

#ifdef HTTP_API_DEBUG
    #define Debug_print(x) Serial.print(x)
    #define Debug_println(x) Serial.println(x)
    #define Debug_write(x, y) Serial.write(x, y)
#else
    #define Debug_print(x)
    #define Debug_println(x)
    #define Debug_write(x, y)
#endif

WiFiSSLClient sslClient;

HTTPAPI_RESULT HTTPAPI_Init(void)
{
    Debug_println(F("HTTPAPI_Init"));

    return (HTTPAPI_OK);
}

void HTTPAPI_Deinit(void)
{
    Debug_println(F("HTTPAPI_Deinit"));
}

HTTP_HANDLE HTTPAPI_CreateConnection(const char* hostName)
{
    Debug_print(F("HTTPAPI_CreateConnection: "));
    Debug_println(hostName);

    WiFiSSLClient* client = &sslClient;

    if (client->connected()) {
        Debug_println(F("Client already connected!"));
        client = NULL;
    } else if (!client->connect(hostName, 443)) {
        Debug_println(F("Client connect failed!"));
        client = NULL;
    }

    return ((HTTP_HANDLE)client);
}

void HTTPAPI_CloseConnection(HTTP_HANDLE handle)
{
    Debug_println(F("HTTPAPI_CloseConnection"));

    WiFiSSLClient* client = (WiFiSSLClient*)handle;

    client->stop();
}

static const char* HTTPRequestTypes[] = {
    "GET",
    "POST",
    "PUT",
    "DELETE",
    "PATCH"
};

HTTPAPI_RESULT HTTPAPI_ExecuteRequest(HTTP_HANDLE handle, 
        HTTPAPI_REQUEST_TYPE requestType, const char* relativePath,
        HTTP_HEADERS_HANDLE httpHeadersHandle, const unsigned char* content,
        size_t contentLength, unsigned int* statusCode,
        HTTP_HEADERS_HANDLE responseHeadersHandle,
        BUFFER_HANDLE responseContent)
{
    Debug_print("HTTPAPI_ExecuteRequest: ");
    Debug_print(HTTPRequestTypes[requestType]);
    Debug_print(F(" "));
    Debug_print(relativePath);
    Debug_print(F(" "));
    Debug_println(F("HTTP/1.1"));

    WiFiSSLClient* client = (WiFiSSLClient*)handle;

    if (!client->connected()) {
        Debug_println(F("Client not connected!"));
        return HTTPAPI_ERROR;
    }

    // request line
    client->print(HTTPRequestTypes[requestType]);
    client->print(F(" "));
    client->print(relativePath);
    client->print(F(" "));
    client->println(F("HTTP/1.1"));

    // headers
    size_t headersCount;
    char* header;

    HTTPHeaders_GetHeaderCount(httpHeadersHandle, &headersCount);

    for (size_t i = 0; i < headersCount; i++) {
        HTTPHeaders_GetHeader(httpHeadersHandle, i, &header);

        Debug_println(header);
        client->println(header);

        free(header);
    }

    // empty line
    Debug_println();
    client->println();

    // body;
    if (contentLength) {
        client->write(content, contentLength);
    }

    // status
    String status = client->readStringUntil('\n');
    status.trim();
    Debug_println(status);

    *statusCode = status.substring(status.indexOf(' ') + 1, status.lastIndexOf(' ')).toInt();

    // headers
    String responseLine;
    contentLength = 0;
    while(true) {
        responseLine = client->readStringUntil('\n');
        responseLine.trim();

        Debug_println(responseLine);

        if (responseLine.length() == 0) {
            break;
        }

        int colonIndex = responseLine.indexOf(':');
        String headerName = responseLine.substring(0, colonIndex);
        String headerValue = responseLine.substring(colonIndex + 1);

        headerName.trim();
        headerValue.trim();

        HTTPHeaders_AddHeaderNameValuePair(responseHeadersHandle, headerName.c_str(), headerValue.c_str());

        if (headerName.equals("Content-Length")) {
            contentLength = headerValue.toInt();
        }
    }


    if (contentLength) {
        BUFFER_pre_build(responseContent, contentLength);
        client->readBytes(BUFFER_u_char(responseContent), contentLength);

        Debug_write(BUFFER_u_char(responseContent), contentLength);
        Debug_println();
        Debug_println();
    }

    return (HTTPAPI_OK);
}

HTTPAPI_RESULT HTTPAPI_SetOption(HTTP_HANDLE handle, const char* optionName,
        const void* value)
{
    Debug_print(F("HTTPAPI_SetOption: "));
    Debug_println(optionName);

    WiFiSSLClient* client = (WiFiSSLClient*)handle;
    HTTPAPI_RESULT result = HTTPAPI_INVALID_ARG;

    if (strcmp("timeout", optionName) == 0) {
        client->setTimeout(*(const unsigned int*)value);

        result = HTTPAPI_OK;
    }

    return result;
}

HTTPAPI_RESULT HTTPAPI_CloneOption(const char* optionName, const void* value,
        const void** savedValue)
{
    Debug_print(F("HTTPAPI_CloneOption: "));
    Debug_println(optionName);

    HTTPAPI_RESULT result = HTTPAPI_INVALID_ARG;

    if (strcmp("timeout", optionName) == 0) {
        unsigned int* timeout = (unsigned int*)malloc(sizeof(unsigned int));

        *timeout = *(const unsigned int*)value;

        *savedValue = &timeout;

        result = HTTPAPI_OK;
    }

    return result;
}
