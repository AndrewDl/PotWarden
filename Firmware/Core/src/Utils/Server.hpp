//web server
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include "config.h"

//Apis
#include "Api/SensorApi.hpp"
#include "Api/ActionsApi.hpp"

#include "Models/Sensors/ISensor.hpp"

AsyncWebServer server(80);

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
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, PUT, POST");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

    SPIFFS.begin();
    
    #ifdef WEB_SERVER_NAME
    if (!MDNS.begin(WEB_SERVER_NAME)) {
        Serial.println("Error setting up MDNS responder!");
        return;
    }
    Serial.println("mDNS responder started");
    #endif
    
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    
    server.on(
        "/*", HTTP_OPTIONS,
        [](AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse(204);
            request->send(response);
        }
    );

    server.on("/health", HTTP_GET, healthRequest);
    server.on("/time", HTTP_GET, getTime);
    server.on("/sensor/data/live", HTTP_GET, getSensorData);
    server.on("/sensor/data/file", HTTP_GET, getDataFile);    
    server.on("/sensor/data/list", HTTP_GET, listDataFiles);
    server.on("/sensor/list", HTTP_GET, listSensors);
    server.on("/action/pour", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, actionPour);

    server.onNotFound(notFound);

    server.begin();
}