#pragma once

#include <map>
#include <Arduino.h>

struct SensorData {
    int Id;
    int Value;
    String TimeStamp;
};

enum SensorType {
    NA = 0,
    VIRTUAL = 1,
    SOIL_CAP = 21,
    TEMPERATURE = 31,
    SMART_SOIL_MOISTURE = 0xF1,
    SMART_AIR_HUMIDITY = 0xF2,
    SMART_SOIL_TEMPERATURE = 0xF3,
    SMART_AIR_TEMPERATURE = 0xF4
};

  /* class SensorMap that implements map data structure
  where the key is the sensor id, represented as int value and the value is a SensorData object 
  with functions that allow to:
  -add pair of id and sensor data object
  -remove pair by id
  -get sensor data by id
  -update and sensor data object by id
  */
class SensorMap {
  private:
    std::map<int, SensorData*> sensorMap;

  public:
    // Add a pair of id and SensorData pointer
    void add(int id, SensorData* data) {
      sensorMap[id] = data;
    }

    // Remove pair by id
    void remove(int id) {
      auto it = sensorMap.find(id);
      if (it != sensorMap.end()) {
        sensorMap.erase(it);
      }
    }

    // Get SensorData pointer by id
    SensorData* get(int id) {
      auto it = sensorMap.find(id);
      if (it != sensorMap.end()) {
        return it->second;
      }
      return nullptr;
    }

    // Update SensorData pointer by id
    void update(int id, SensorData* data) {
      auto it = sensorMap.find(id);
      if (it != sensorMap.end()) {
        it->second = data;
      }
    }
};