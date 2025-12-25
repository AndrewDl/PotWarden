#pragma once
#include <Arduino.h>

// Represents an action request for an actuator
// @param deviceId The unique identifier of the device to control
// @param actionName The name of the action to perform
// @param value The value or parameter for the action
// @return Struct containing action request data
struct ActionRequest {
    String deviceId;
    String actionName;
    int value;
};