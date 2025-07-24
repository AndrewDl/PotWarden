#pragma once

class InternalTempSensor : public ISensor {
    public:
        InternalTempSensor(int Id){
            this->Id = Id;
            this->Type = TEMPERATURE;
            this->Name = "InternalTempSensor";
        }

        void Init() override{

        }

        SensorData* Read() override {  // Method/function defined inside the class
            srand(UTC.second());
        
            SensorData *data = new SensorData();
            
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime();

            data->Value = temperatureRead();

            return data;
        }
};