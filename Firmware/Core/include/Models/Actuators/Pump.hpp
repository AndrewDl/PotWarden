#pragma once
#include "IActuator.hpp"

/// @brief Class representing watter pump
/// Watter pump can be turned on for a specific duration
/// @warning: If running for a duration with RunImmediately it will block the MC untill completion
class Pump : public IActuator {
private:
    int outputPin;
    
    /// @brief flag for keeping internal state. 0 inactive pump. 1 - active pump
    int state;
    
    /// @brief 
    unsigned long actionMillis;
    
    /// @brief Duration for which the pump should run
    unsigned long duration;

    bool RunConditionMet();

public:
    /// @brief Constructor for Pump instance
    /// @param outputPin GPIO pin connected to the pump control
    Pump(int outputPin);

    /// @brief Initialize the actuator, Usually setting up pins and IO modes
    virtual void Init();

    /// @brief Set the pump to run for a speccified ammount of time
    /// @param duration time in milliseconds
    virtual void SetAction(unsigned int duration);

    /// @brief Run the action, that takes time to complete in the background
    /// Execute inside the time loop
    /// if action is not set with SetAction(unsigned int) before invoking
    /// this function, nothing will happen
    /// @attention Configure the action with SetAction(unsigned int) prior to calling this function
    /// @param currentMillis current time in milliseconds from millis()
    virtual void RunAction(unsigned int currentMillis);

    /// @brief Run pump for setted time immediately, blocking the execution until complete
    /// if action is not set with SetAction(unsigned int) before invoking
    /// this function, nothing will happen
    /// @attention Configure the action with SetAction(unsigned int) prior to calling this function
    /// @warning This will block the execution until the action is completed
    virtual void RunAction();

    /// @brief Get the current state of the watter pump
    /// @return Possible states:
    /// 0 - inactive
    /// 1 - active
    virtual int GetState();
};
