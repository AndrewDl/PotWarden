#include <ESPAsyncWebServer.h>
#pragma once

bool paramIsNull(AsyncWebServerRequest *request, char *paramName)
{
    return request->getParam(paramName) == NULL;  
}

bool isValidInteger(AsyncWebServerRequest *request, char *paramName)
{
    if (paramIsNull(request, paramName)) 
    {
        return false;
    }   

    String value = request->getParam(paramName)->value();
    
    for (int i = 0; i < value.length(); i++)
    {
        if (!isDigit(value[i]))
        {
            return false;
        }
    }
    
    return true;
}