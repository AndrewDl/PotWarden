#pragma once

#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "Utils/FileSystem.hpp"
#include "Models/Sensors/ISensor.hpp"

#include "Api/ApiTools.hpp"



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
    bool requestedAsFile = false;


    if (!isValidString(request, paramName))
    {
        String message = "Server error"; 
        request->send(500, "text/plain", message);
        return;
    }

    if (request->hasParam("download")) {
        requestedAsFile = request->getParam("download")->value() == "true";
    }
    
    String fileName = (String)READINGS_DIR + (String)"/" + request->getParam("file")->value();
    
    Serial.println("File requested: " + fileName);
    Serial.println("File exists: " + String(SPIFFS.exists(fileName)));
    
    if(!FileSystem::Exists(fileName)){
      request->send(404, "text/plain", "File not found");
      return;
    }
    Serial.println("File found...");

    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, fileName, "text/plain", requestedAsFile);  
    request->send(response);    
}

void listDataFiles(AsyncWebServerRequest *request) {
    // Lists all files in the "readings" directory using FileSystem
    // @param request Pointer to the AsyncWebServerRequest
    // @return Sends a JSON response with a "files" array or error message

    Serial.println("Retrieveing files...");

    std::vector<String> filesVec = FileSystem::List(READINGS_DIR);
    if (filesVec.empty()) {
        request->send(404, "application/json", "{\"error\":\"No files found\"}");
        return;
    }

    JsonDocument jsonDoc;
    JsonArray filesArray = jsonDoc["files"].to<JsonArray>();
    for (const auto& file : filesVec) {
        filesArray.add(file);
    }

    AsyncResponseStream *response = request->beginResponseStream("application/json");
    serializeJson(jsonDoc, *response);
    request->send(response);
}
