#pragma once

#include "Models/SensorDataStructs.hpp"

/// @brief Interface that defines a sensor
/// it defines the basic methods and properties that a sensor must have
class ISensor {
    public:
        int Id;
        String Name;
        SensorType Type;

        virtual void Init() = 0;
        virtual SensorData* Read() = 0;
};