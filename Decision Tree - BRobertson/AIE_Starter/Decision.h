#pragma once
#include "Agent.h"

class Decision
{
public:
    virtual ~Decision() = default;
    virtual void Execute(Agent* agent, float deltaTime) = 0; // Execute decision/action
};