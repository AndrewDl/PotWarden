#include <Arduino.h>
#include <ezTime.h>

#include "TimeIntervals.h"

#include "myWiFi.hpp"
#include "Server.hpp"
//config file
#include "config.h"
#include "BoardEsp32c3.h"

#include "Models/Sensors/ISensor.hpp"
#include "Models/Sensors/MoistureSensor.hpp"
#include "Models/Sensors/TemperatureSensor.hpp"
#include "Models/Sensors/InternalTemperatureSensor.hpp"
#include "Models/Sensors/VirtualSensor.hpp"

ISensor *sensorArray[] = { 
    new MoistureSensor(201, A0),
    new InternalTempSensor(301),
    new TemperatureSensor(302, A1),
    new VirtualSensor(101),
  };

int sensorArraySize = sensorArraySize = sizeof(sensorArray)/sizeof(sensorArray[0]);

SensorData **data = new SensorData*[sensorArraySize];

// put function declarations here:  
void GatherSensorData();

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
  InitServer();  
  waitForSync();

  // Init sensors
  for (int i = 0; i < sensorArraySize; i++){
    sensorArray[i]->Init();
    data[i] = sensorArray[i]->Read();
  } 
}

unsigned long ledMillis = 0;
unsigned long sensorMillis = 0;
bool ledState = LOW;

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - ledMillis >= INTERVAL_STATUS_LED) {
    ledMillis = currentMillis;  // Remember the time

    ledState = !ledState;            // Toggle the LED state
    digitalWrite(PCB_LED, ledState);
  }

  if (currentMillis - sensorMillis >= INTERVAL_READ_SENSORS) {
    sensorMillis = currentMillis;

    GatherSensorData();
  }  
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