#include <Wire.h>
#include <Arduino.h>

//Command Data packet structure:
//||    Byte 0  |    Byte 1  |    Byte 2  ||
//||  HEADER H  |  HEADER L  |  CHECKSUM  ||
//||--CCCCCCCC--|--OOOOOOOO--|--XXXXXXXX--||
// CC : Commmand 8 bits; 0x10 - Request Data, 0x20 : Set Action
// OO : Commmand operand; 0x10 - Sensor 1; 0x20 - Sensor 2
// XX : Checksum. XOR of bytes 2,1,0

//Response Data packet structure:
//||    Byte 0  |    Byte 1  |    Byte 2  |   Byte 3   |   Byte 4   ||
//||  HEADER H  |  HEADER L  |  CHECKSUM  |   Value H  |   Value L  ||
//||--IIIIIIII--|--SSS000BB--|--XXXXXXXX--|--HHHHHHHH--|--LLLLLLLL--||
// XX : Checksum. XOR of bytes 3,1,0
// BB - ADC Bits. 00: None, 01: 10bits; 10:12bits; 11:16bits
// SS - SensorType Type. 
//      000: none, 
//      001: MOISTURE, 
//      010: HUMIDITY, 
//      011: SOIL TEMPERATURE, 
//      100: AIR TEMPERATURE
//
// II - Device Signature.
// 00 - RESERVED

// Defines for AtTinyX5 family
#ifdef ARDUINO_AVR_ATTINYX5
  #define LED_PIN PB4
#endif

// Defines for AtTiny 402 family
#ifdef ARDUINO_attinyxy2
  #define LED_PIN 4
#endif

#define DEVICE_ID 0x5A //Device Signature typical for PotWarden I2C Sensor controllers
#define DEVICE_I2C_ADDR 0x08

#define CMD_REQUEST_DATA 0x10
#define CMD_SET_ACTION   0x20

#define SENSOR_TYPE_NONE 0x00
#define SENSOR_TYPE_MOISTURE 0x10
#define SENSOR_TYPE_TEMPERATURE 0x20

#define ADC_BITS_NONE 0x00
#define ADC_BITS_10 0x01

void requestEvent();
void receiveEvent(int howMany);
uint8_t* packResponseData(unsigned int value);
uint8_t* decodeCommandData(int howMany);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(DEVICE_I2C_ADDR);  // join I2C bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
}

unsigned int sensorValue = 0;
void loop() {
  sensorValue = analogRead(A3); // read the sensor value
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(uint8_t(sensorValue & 0xFF));
  Wire.write(uint8_t((sensorValue >> 8) & 0xFF));
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    uint8_t c = Wire.read(); // receive byte as a character
    if (c == 0x23) {
      digitalWrite(LED_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
    } else if (c == 0x34) {
      digitalWrite(LED_PIN, LOW);  // turn the LED off by making the voltage LOW
    }
  }
}

uint8_t* packResponseData(unsigned int value) {
  uint8_t* buffer = new uint8_t[5];
  buffer[0] = (DEVICE_ID << 4) | 0x0; //Device ID and reserved bits
  buffer[1] = 0x00 | (SENSOR_TYPE_MOISTURE << 2) | ADC_BITS_10; //Sensor Type and ADC bits
  buffer[2] = buffer[0] ^ buffer[1] ^ (value & 0xFF) ^ ((value >> 8) & 0xFF); //Checksum
  buffer[3] = (value >> 8) & 0xFF; //Value High byte
  buffer[4] = value & 0xFF;        //Value Low byte
  return buffer;
}

uint8_t* decodeCommandData(int howMany) {
  if (howMany < 3) return nullptr; //Invalid command length
  uint8_t* buffer = new uint8_t[3];
  for (int i = 0; i < 3; i++) {
    buffer[i] = Wire.read();
  }
  //Verify checksum
  uint8_t checksum = buffer[0] ^ buffer[1];
  if (checksum != buffer[2]) {
    delete[] buffer;
    return nullptr; //Checksum mismatch
  }
  return buffer;
}