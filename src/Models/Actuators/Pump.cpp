#include "Pump.hpp"
#include <Arduino.h>

Pump::Pump(int outputPin) : outputPin(outputPin), state(0) {
    // Constructor implementation (if needed)
}

void Pump::Init() {
    pinMode(outputPin, OUTPUT);
}

void Pump::Act(unsigned int value) {
    digitalWrite(outputPin, HIGH);
    delay(value);
    digitalWrite(outputPin, LOW);
    // TODO: Implement actuator logic
}

int Pump::GetState() {
    // TODO: Implement state retrieval logic
    return 0;
}
