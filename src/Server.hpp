//web server
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include "config.h"

//Apis
#include "SensorApi.hpp"

AsyncWebServer server(80);

int *model;
ISensor **mySensorArrayModel;

void healthRequest(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "The service is up and running");
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void InitServer()
{ 
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, PUT");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

    SPIFFS.begin();
    MDNS.begin(WEB_SERVER_NAME);

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/health", HTTP_GET, healthRequest);
    server.on("/time", HTTP_GET, getTime);
    server.on("/sensor", HTTP_GET, getSensor);
    server.on("/listSensors", HTTP_GET, listSensors);

    server.onNotFound(notFound);

    server.begin();
}