#include <Arduino.h>
#include <ezTime.h>

#include "Utils/myWiFi.hpp"
#include "Utils/Server.hpp"
#include "Utils/FileSystem.hpp"
//config file
#include "config.h"
#include "boardEsp32c3.h"
//sensors
#include "Models/Sensors/ISensor.hpp"
#include "Models/Sensors/MoistureSensor.hpp"
#include "Models/Sensors/TemperatureSensor.hpp"
#include "Models/Sensors/InternalTemperatureSensor.hpp"
#include "Models/Sensors/VirtualSensor.hpp"
#include "Models/SensorDataStructs.hpp"
//actuators
#include "Models/Actuators/IActuator.hpp"
#include "Models/Actuators/Pump.hpp"

#ifdef ENVIRONMENT_TEST
ISensor *sensorArray[] = { 
    //new MoistureSensor(201, A0),
    new InternalTempSensor(301),
    //new TemperatureSensor(302, A1),
    new VirtualSensor(101),
  };
#endif

#ifdef ENVIRONMENT_RELEASE
ISensor *sensorArray[] = { 
    new MoistureSensor(201, A0),
    new InternalTempSensor(301),
    new TemperatureSensor(302, A1),
  };
#endif

IActuator *actuatorArray[] = { 
    new Pump(GPIO10),
  };

int sensorArraySize = sizeof(sensorArray)/sizeof(sensorArray[0]);
int actuatorArraySize = sizeof(actuatorArray)/sizeof(actuatorArray[0]);

SensorData **data = new SensorData*[sensorArraySize];

// put function declarations here:  
void LogSensorData();
void GatherSensorData();
void ExecuteActions();

void setup() {
  // put your setup code here, to run once:
  setDebug(INFO);
  Serial.begin(9600);
  delay(5000);

  //hardware stuff
  pinMode(PCB_LED, OUTPUT);
  //end hardware init stuff

  char ssid[] = WIFI_SSID;
  char wifi_pass[] = WIFI_PASSWORD;
  InitWiFi(ssid, wifi_pass);  
  waitForSync();
  
  // Init sensors
  for (int i = 0; i < sensorArraySize; i++){
    sensorArray[i]->Init();
  } 
  // Init actuators
  for (int i = 0; i < actuatorArraySize; i++){
    actuatorArray[i]->Init();
  }

  Serial.println("Sensors initialized.");

  GatherSensorData();

  delay(1000);
  InitServer();  
}

unsigned long ledMillis = 0;
unsigned long sensorMillis = 0;
unsigned long actionMillis = 0;
unsigned long sensorDataMillis = 0;
bool ledState = LOW;

void loop() {
  unsigned long currentMillis = millis();
  
  //Status LED blinking section
  if (currentMillis - ledMillis >= INTERVAL_STATUS_LED) {
    ledMillis = currentMillis;  // Remember the time

    ledState = !ledState;            // Toggle the LED state
    digitalWrite(PCB_LED, ledState);
  }

  //Sensor reading section
  if (currentMillis - sensorMillis >= INTERVAL_READ_SENSORS) {
    sensorMillis = currentMillis;

    GatherSensorData();

    //Auto pour if conditions are met
    #ifdef ENABLE_AUTO_POUR
    if (data[0]->Value >= MOISTURE_THRESHOLD_DRY) {
      actuatorArray[0]->SetAction(AUTO_POUR_DURATION); //set pump to run for 20 seconds
      Serial.println("Warning: Soil moisture is very low!");
    }
    #endif
  }

  //Actions execution section
  #ifdef ENABLE_ACTIONS_EXECUTION
  if (currentMillis - actionMillis >= INTERVAL_CHECK_ACTIONS) {
    actionMillis = currentMillis;

    ExecuteActions();
  }
  #endif

  //Sensor data logging section
  #ifdef ENABLE_READINGS_LOGGING
  if (currentMillis - sensorDataMillis >= INTERVAL_LOG_SENSOR_DATA) {
    sensorDataMillis = currentMillis;
    LogSensorData();
  }
  #endif
}

void GatherSensorData(){
  for (int i = 0; i < sensorArraySize; i++){
    data[i] = sensorArray[i]->Read();

    Serial.print("| time: ");
    Serial.print(data[i]->TimeStamp);
    Serial.print(" | sensor id: ");
    Serial.print(data[i]->Id);
    Serial.print(" | value: ");
    Serial.println(data[i]->Value);
  } 
}

void ExecuteActions(){
  for (int i = 0; i < actuatorArraySize; i++){
    actuatorArray[i]->RunAction(millis());
  }
}

void LogSensorData(){
  for (int i = 0; i < sensorArraySize; i++){
    data[i] = sensorArray[i]->Read();
    
    String dataRow = data[i]->TimeStamp + ";" + data[i]->Value;
    String fileDate = UTC.dateTime(DATETIME_FORMAT_DATEONLY);
    String fileName = fileDate + "_" + data[i]->Id + ".csv";
    String fullFileName = String(READINGS_DIR) + "/" + fileName;

    Serial.print("Opening file: ");
    Serial.println(fullFileName);

    #ifdef ENABLE_READINGS_LOGGING
      FileSystem::Append(fullFileName, dataRow);
    #endif
    
    Serial.print("Appended data row: ");
    Serial.println(dataRow);
  } 
}
