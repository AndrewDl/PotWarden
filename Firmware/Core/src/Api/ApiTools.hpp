#pragma once
#include <ESPAsyncWebServer.h>

bool paramIsNull(AsyncWebServerRequest *request, char *paramName);
bool isValidInteger(AsyncWebServerRequest *request, char *paramName);
bool isValidString(AsyncWebServerRequest *request, char *paramName);