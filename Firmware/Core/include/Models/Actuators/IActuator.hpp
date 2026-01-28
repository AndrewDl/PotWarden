#pragma once

/// @brief Interface for all actuator devices.
class IActuator {
public:
    virtual ~IActuator() {}

    /// @brief Initialize the actuator, Usually setting up pins and IO modes
    virtual void Init() = 0;

    /// @brief Set the device to perform its action
    /// @param value can have diffrent meanings depending on the device
    virtual void SetAction(unsigned int value) = 0;

    /// @brief Run the action, that takes time to complete in the background
    /// Execute inside the time loop
    /// @param currentMillis current time in milliseconds from millis()
    virtual void RunAction(unsigned int currentMillis) = 0;

    /// @brief Run the action immediately, possibly blocking the execution until complete
    /// Used for simple actuator actions that can occur immediately
    virtual void RunAction() = 0;

    /// @brief Get the current state of the actuator
    /// @return The current state of the actuator, 
    /// normally 0 - inactive/default state
    ///other value - may depend on specific actuator
    virtual int GetState() = 0;
};
