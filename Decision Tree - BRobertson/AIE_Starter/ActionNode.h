#pragma once
#include "Decision.h"
#include "Behaviour.h"
#include "Agent.h"

class ActionNode : public Decision
{
private:
    Behaviour* m_behaviour; // The behavior to execute

public:
    ActionNode(Behaviour* behaviour) : m_behaviour(behaviour) {}
    virtual ~ActionNode() { delete m_behaviour; }
    void Execute(Agent* agent, float deltaTime);
};