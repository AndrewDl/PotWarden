#pragma once

struct SensorData {
    int Id;
    int Value;
    String TimeStamp;
};

enum SensorType {
    NA = 0,
    VIRTUAL = 1,
    SOIL_CAP = 21,
    TEMPERATURE = 31
};

class ISensor {
    public:
        int Id;
        String Name;
        SensorType Type;

        virtual SensorData* Read() = 0;
};

class VirtualSensor : public ISensor {
    public:
        VirtualSensor(int Id){
            this->Id = Id;
            this->Type = VIRTUAL;
            this->Name = "VirtualSensor";
        }

        SensorData* Read() {  // Method/function defined inside the class
            srand(UTC.second());
        
            SensorData *data = new SensorData();
            
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime();

            data->Value = rand() % 3600 + 1650;

            return data;
        }
};

class InternalTempSensor : public ISensor {
    public:
        InternalTempSensor(int Id){
            this->Id = Id;
            this->Type = TEMPERATURE;
            this->Name = "InternalTempSensor";
        }

        SensorData* Read() {  // Method/function defined inside the class
            srand(UTC.second());
        
            SensorData *data = new SensorData();
            
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime();

            data->Value = temperatureRead();

            return data;
        }
};

class MoistureSensor : public ISensor {
    public:
        int Pin;

        MoistureSensor(int Id, int Pin){
            this->Id = Id;
            this->Pin = Pin;
            this->Type = SOIL_CAP;
            this->Name = "SoilMoisture";

            pinMode(Pin, INPUT);
        }

        SensorData* Read() {  // Method/function defined inside the class
            srand(UTC.second());

            SensorData *data = new SensorData();
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime();

            data->Value = analogRead(this->Pin);

            return data;
        }
};