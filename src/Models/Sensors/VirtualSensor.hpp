#pragma once

class VirtualSensor : public ISensor {
    public:
        VirtualSensor(int Id){
            this->Id = Id;
            this->Type = VIRTUAL;
            this->Name = "VirtualSensor";
        }

        void Init() override {
            srand(millis());
        }
        
        SensorData* Read() override {  // Method/function defined inside the class
                    
            SensorData *data = new SensorData();
            
            data->Id = this->Id;
            data->TimeStamp = UTC.dateTime();

            data->Value = rand() % 3600 + 1650;

            return data;
        }
};