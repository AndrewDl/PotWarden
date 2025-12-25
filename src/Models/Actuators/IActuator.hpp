#pragma once

class IActuator {
public:
    virtual ~IActuator() {}
    virtual void Init() = 0;
    virtual void Act(unsigned int value) = 0;
    virtual int GetState() = 0;
};
