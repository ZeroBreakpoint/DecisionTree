#include "Agent.h"
#include "Behaviour.h"

using namespace AIForGames;

void Agent::Update(float deltaTime)
{
    if (m_current)
        m_current->Update(this, deltaTime);
        m_pathAgent.Update(deltaTime);
}

void Agent::Draw()
{
    // Get the agent's current position from the PathAgent
    glm::vec2 position = m_pathAgent.GetPosition();

    // Set the radius of the agent's representation
    float radius = 8.0f;

    // Draw the agent as a circle on the screen using raylib's DrawCircle function
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), radius, m_color);
}

void Agent::GoTo(glm::vec2 point)
{
    // Find the closest node to the clicked position (end node)
    AIForGames::Node* end = m_nodeMap->GetClosestNode(point);


    if (end != nullptr)
    {
        m_pathAgent.GoToNode(end, *m_nodeMap);
    }
}

// Reset function clears the current path, stopping any pathfinding movement.

void Agent::Reset()
{
    m_pathAgent.ClearPath();  // Clear the current path from the pathfinding agent
}


// Constructor for the Agent class
Agent::Agent() : m_current(nullptr),m_nodeMap(nullptr), m_color({ 255, 255, 0, 255 }),m_target(nullptr)
{
  
}


Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour): m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }), m_target(nullptr)
{
 
}

// Destructor for the Agent class

Agent::~Agent()  
{ 
    //delete m_current;  // Free the memory allocated for the current behavior
}

// PathComplete function checks if the agent has completed its path.  It returns true if there are no more nodes in the path.
bool Agent::PathComplete() const
{
    return m_pathAgent.GetPath().empty();  // Returns true if the path is empty
} 
