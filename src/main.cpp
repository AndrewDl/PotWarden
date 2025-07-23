#include <Arduino.h>
#include <ezTime.h>

#include "myWiFi.hpp"
#include "Server.hpp"
//config file
#include "config.h"
#include "BoardEsp32c3.h"

#include "Models/SensorDataStructs.hpp"

ISensor *sensorArray[] = { 
    new VirtualSensor(101),
    new VirtualSensor(102),
    new MoistureSensor(201, A0),
    new InternalTempSensor(301),
  };

int sensorArraySize = sensorArraySize = sizeof(sensorArray)/sizeof(sensorArray[0]);

SensorData **data = new SensorData*[sensorArraySize];

// put function declarations here:  
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
}

void loop() {
  for (int i = 0; i < sensorArraySize; i++){
    data[i] = sensorArray[i]->Read();

    Serial.print("time: ");
    Serial.print(data[i]->Id);
    Serial.print("sensor: ");
    Serial.print(data[i]->TimeStamp);
    Serial.print("value: ");
    Serial.println(data[i]->Value);

  }    
  // put your main code here, to run repeatedly:
  // Serial.println("UTC: " + UTC.dateTime());
    
  digitalWrite(PCB_LED, HIGH);
  delay(2000);
  digitalWrite(PCB_LED, LOW);
  delay(2000);
}