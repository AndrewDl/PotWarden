#pragma once

/// @brief Sensor that generates virtual sensor data used as stub for testing
/// Implements the ISensor interface
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
            data->TimeStamp = UTC.dateTime(DATETIME_FORMAT_DEFAULT);

            data->Value = rand() % 3600 + 1650;

            return data;
        }
};