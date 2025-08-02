#pragma once

#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "Api/ApiTools.hpp"

#include "Models/Sensors/ISensor.hpp"

extern ISensor *sensorArray[];
extern int sensorArraySize;
extern SensorData **data;

void getTime(AsyncWebServerRequest *request) {
    String message = UTC.dateTime();
    Serial.println(message);
    request->send(200, "text/plain", message);
}

void getSensorData(AsyncWebServerRequest *request) {
      
    char paramName[] = "id";

    if (!isValidInteger(request, paramName))
    {
        String message = "Server error"; 
        request->send(500, "text/plain", message);
        
        return;
    }

    int sensorNum = request->getParam("id")->value().toInt();
    
    JsonDocument jsonDoc;   
    jsonDoc["id"] = data[sensorNum]->Id;   
    jsonDoc["value"] = data[sensorNum]->Value;   
    jsonDoc["timeStamp"] = data[sensorNum]->TimeStamp;  

    AsyncResponseStream *response = request->beginResponseStream("application/json");
    serializeJson(jsonDoc, *response);
    request->send(response);
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

void getDataFile(AsyncWebServerRequest *request) {
      
    char paramName[] = "file"; 

    if (!isValidString(request, paramName))
    {
        String message = "Server error"; 
        request->send(500, "text/plain", message);
        return;
    }

    String fileName = request->getParam("file")->value();

    if(!SPIFFS.exists(fileName)){
      request->send(404, "text/plain", "File not found");
      return;
    }

    Serial.println("File found...");

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, fileName, "text/plain", false);  
    request->send(response);    
}

void listDataFiles(AsyncWebServerRequest *request) {
      
    char paramName[] = "file"; 

    if (!isValidString(request, paramName))
    {
        String message = "Server error"; 
        request->send(500, "text/plain", message);
        return;
    }

    String fileName = request->getParam("file")->value();

    if(!SPIFFS.exists(fileName)){
      request->send(404, "text/plain", "File not found");
      return;
    }
    
    Serial.println("File found...");

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, fileName, "text/plain", false);  
    request->send(response);    
}
