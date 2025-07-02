#pragma once

#include <ArduinoJson.h>

#include "ApiTools.hpp"
#include "Models/SensorDataStructs.hpp"

extern ISensor *sensorArray[];
extern int sensorArraySize;
extern SensorData **data;

void getTime(AsyncWebServerRequest *request) {
    String message = UTC.dateTime();
    Serial.println(message);
    request->send(200, "text/plain", message);
}

void getSensor(AsyncWebServerRequest *request) {
    String message = "Server error";    
    char paramName[] = "id";

    if (isValidInteger(request, paramName))
    {
        int sensorNum = request->getParam("id")->value().toInt();
        message = data[sensorNum]->value;   
        //message = request->getParam("id")->value();
    }    
    Serial.println(message);
    request->send(200, "text/plain", message);
}

void listSensors(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");

    Serial.println("listing sensors...");

    JsonDocument jsonDoc;

    for(int i = 0; i < sensorArraySize; i++)
    {
        JsonDocument object;
        object["id"] = sensorArray[i]->Id;
        object["name"] = sensorArray[i]->Name;
        object["type"] = sensorArray[i]->Type;

        jsonDoc.add(object);
    }
            
    serializeJson(jsonDoc, *response);
    
    request->send(response);
}
