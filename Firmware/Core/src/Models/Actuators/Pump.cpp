#include "Pump.hpp"
#include <Arduino.h>

Pump::Pump(int outputPin) : outputPin(outputPin), state(0) {
    // Constructor implementation (if needed)
    this->actionMillis = 0;
    this->duration = 0;
    this->state = 0;
}

// Returns true if the pump is inactive and duration is set
// @return True if pump can run, false otherwise
bool Pump::RunConditionMet() {
    return (this->state == 0 && this->duration != 0);
}

void Pump::Init() {
    pinMode(outputPin, OUTPUT);
}

void Pump::SetAction(unsigned int duration) {
    // avoid resetting if pump is already set for action
    if (this->state != 0 || this->duration != 0) return;

    this->duration = duration;
}

void Pump::RunAction(unsigned int currentMillis) {
    // Activating the pump if not active and duration is set
    if (this->state == 0 && this->duration != 0) {
        this->actionMillis = currentMillis;
        this->state = 1; // Set state to active

        digitalWrite(outputPin, HIGH); // Turn on the pump
    }
    // If state was active, check if duration has elapsed to turn off the pump
    if (this->state == 1 && (currentMillis - this->actionMillis > this->duration)) {
        digitalWrite(outputPin, LOW); // Turn off the pump

        // Reset pump state
        this->state = 0;
        this->actionMillis = 0;
        this->duration = 0;
    } 
}

void Pump::RunAction() {
    if (!this->RunConditionMet()) return;

    this->state = 1; // Set state to active
    digitalWrite(outputPin, HIGH); // Turn on the pump
    delay(this->duration); // Blocking delay for the duration
    digitalWrite(outputPin, LOW); // Turn off the pump
    this->duration = 0; // Reset duration
    this->state = 0; // Set state to inactive
}

int Pump::GetState() {    
    return this->state;
}
