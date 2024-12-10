#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <raylib.h>
#include <cfloat>
#include "Behaviour.h"
#include "PathAgent.h"
#include "NodeMap.h"
#include "Pathfinding.h"
#include "Agent.h"
#include "WanderBehaviour.h"

class GoToPointBehaviour : public Behaviour
{
public:
    GoToPointBehaviour() : m_startSet(false), m_endSet(false), m_startNode(nullptr), m_endNode(nullptr) {}  // Constructor initialises the state of the start and end nodes as not set.

    virtual void Update(Agent* agent, float deltaTime); // This function is responsible for updating the behaviour of the agent each frame.  It checks if the start and end points have been set, and guides the agent accordingly.

private:
    bool m_startSet;  // Flag to check if the start point has been set
    bool m_endSet;  // Flag to check if the end point has been set
    AIForGames::Node* m_startNode;  // Pointer to the start node for pathfinding
    AIForGames::Node* m_endNode;  // Pointer to the end node for pathfinding
};

