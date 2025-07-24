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