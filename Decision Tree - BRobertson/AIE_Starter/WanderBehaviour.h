#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <raylib.h>
#include <cfloat>
#include "Behaviour.h"
#include "Agent.h"
#include "NodeMap.h"
#include "PathAgent.h"
#include "Pathfinding.h"

class WanderBehaviour : public Behaviour
{
public:
    WanderBehaviour() : m_lastNode(nullptr) {}  // Constructor initializes the last visited node pointer to nullptr.

    virtual void Update(Agent* agent, float deltaTime);   // It updates the agent based on the wandering logic and the deltaTime (time since last frame).

    void Enter(Agent* agent);  // Enter function is called when the agent first switches to this behaviour.

private:
    AIForGames::Node* m_lastNode; // Track the last node visited
};