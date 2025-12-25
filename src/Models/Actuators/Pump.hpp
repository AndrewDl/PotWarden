#pragma once
#include "IActuator.hpp"

class Pump : public IActuator {
private:
    int outputPin;
    int state;
public:
    Pump(int outputPin);
    void Init() override;
    void Act(unsigned int value) override;
    int GetState() override;
};
