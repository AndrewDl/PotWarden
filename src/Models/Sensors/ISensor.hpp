#pragma once

#include "Models/SensorDataStructs.hpp"

class ISensor {
    public:
        int Id;
        String Name;
        SensorType Type;

        virtual void Init() = 0;
        virtual SensorData* Read() = 0;
};