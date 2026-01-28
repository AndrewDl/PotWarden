#include "OneWire.h"
#include "DallasTemperature.h"

#pragma once

/// @brief Sensor that reads soil temperature using a 
/// Dallas OneWire temperature sensor
/// Implements the ISensor interface
class TemperatureSensor : public ISensor {

    private:
        OneWire oneWire;
        DallasTemperature sensors;

    public:
        int Pin;
        int Data;
        TemperatureSensor(int Id, int Pin){
            this->Id = Id;
            this->Pin = Pin;
            this->Type = TEMPERATURE;
            this->Name = "SoilTemperature";

            this->oneWire = OneWire(Pin);
            this->sensors = DallasTemperature(&oneWire);
        }

        void Init() override {
            this->sensors.begin();
        }

        SensorData* Read() override {  // Method/function defined inside the class
            srand(UTC.second());
        
            SensorData *data = new SensorData();
            
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime(DATETIME_FORMAT_DEFAULT);
            
            this->sensors.requestTemperatures();
            data->Value = this->sensors.getTempCByIndex(0);

            return data;
        }
};