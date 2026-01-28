#pragma once

/// @brief Sensor that reads soil moisture using a 
/// capacitive moisture sensor v2
/// Implements the ISensor interface
class MoistureSensor : public ISensor {
    public:
        int Pin;

        MoistureSensor(int Id, int Pin){
            this->Id = Id;
            this->Pin = Pin;
            this->Type = SOIL_CAP;
            this->Name = "SoilMoisture";            
        }

        void Init() override {
            pinMode(Pin, INPUT);
        }

        SensorData* Read() override {  // Method/function defined inside the class
            srand(UTC.second());

            SensorData *data = new SensorData();
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime(DATETIME_FORMAT_DEFAULT);

            data->Value = analogRead(this->Pin);

            return data;
        }
};