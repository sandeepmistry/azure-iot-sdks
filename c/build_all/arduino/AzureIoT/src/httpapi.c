#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sdk/httpapi.h"
#include "sdk/strings.h"


HTTPAPI_RESULT HTTPAPI_Init(void)
{
    return (HTTPAPI_OK);
}

void HTTPAPI_Deinit(void)
{
}

HTTP_HANDLE HTTPAPI_CreateConnection(const char* hostName)
{    
    return ((HTTP_HANDLE) NULL);
}

void HTTPAPI_CloseConnection(HTTP_HANDLE handle)
{
}

HTTPAPI_RESULT HTTPAPI_ExecuteRequest(HTTP_HANDLE handle, 
        HTTPAPI_REQUEST_TYPE requestType, const char* relativePath,
        HTTP_HEADERS_HANDLE httpHeadersHandle, const unsigned char* content,
        size_t contentLength, unsigned int* statusCode,
        HTTP_HEADERS_HANDLE responseHeadersHandle,
        BUFFER_HANDLE responseContent)
{
    return (HTTPAPI_OK);
}

HTTPAPI_RESULT HTTPAPI_SetOption(HTTP_HANDLE handle, const char* optionName,
        const void* value)
{
    return (HTTPAPI_INVALID_ARG);
}

HTTPAPI_RESULT HTTPAPI_CloneOption(const char* optionName, const void* value,
        const void** savedValue)
{
    return (HTTPAPI_INVALID_ARG);
}
