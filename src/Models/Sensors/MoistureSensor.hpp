#pragma once

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
            data->TimeStamp = UTC.dateTime();

            data->Value = analogRead(this->Pin);

            return data;
        }
};