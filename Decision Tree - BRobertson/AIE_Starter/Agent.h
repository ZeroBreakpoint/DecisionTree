#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <raylib.h>
#include <cfloat>
#include "PathAgent.h"
#include "NodeMap.h"
#include "Behaviour.h"
#include "FollowBehaviour.h"


class Agent
{
public:
    Agent();
    Agent(NodeMap* _nodeMap, Behaviour* _behaviour);  // Parameterised constructor for initializing an agent with a specific behaviour and node map
    ~Agent();  // Destructor
    bool PathComplete() const;  // Checks if the path assigned to the agent is complete
    void Update(float deltaTime);  // Updates the agent's state and behaviour every frame based on delta time
    void Draw();  // Draws the agent to the screen (assumes raylib is used for rendering)
    void GoTo(glm::vec2 point);  // Initiates pathfinding to a given point on the map
    void SetNode(AIForGames::Node* node) { m_pathAgent.SetNode(node); }   // Sets the current node where the agent is located
    void SetSpeed(float speed) { m_pathAgent.SetSpeed(speed); }   // Sets the movement speed of the agent
    void GoToNode(AIForGames::Node* node) { GoTo(node->position); }  // Directs the agent to a specific node in the NodeMap (using the node's position)
    PathAgent& GetPathAgent() { return m_pathAgent; }  // Returns a reference to the internal PathAgent object, which handles pathfinding logic
    NodeMap* GetNodeMap() const { return m_nodeMap; }   // Returns the NodeMap that the agent uses for navigation
    Agent* GetTarget() const { return m_target; }  // Gets the current target (if any) that the agent is following or interacting with
    glm::vec2 GetPosition() const { return m_pathAgent.GetPosition(); }  // Returns the agent's current position in the world as a 2D vector
    void SetBehaviour(Behaviour* behaviour) { m_current = behaviour; }
    Behaviour* GetBehaviour() const { return m_current; }
    void SetTarget(Agent* target) { m_target = target; }  // Sets the agent's target (another agent to follow or interact with)
    void SetColor(Color color) { m_color = color; }  // Changes the agent's color (used for drawing/visual representation)
    void Reset();  // Resets the agent's state, including clearing its current path or target
   
private:
    PathAgent m_pathAgent;  // The internal PathAgent used for pathfinding logic and navigation
    Behaviour* m_current = nullptr;  // Pointer to the current behaviour (e.g., Follow, Wander, etc.)
    NodeMap* m_nodeMap = nullptr;  // Pointer to the NodeMap (graph-like structure used for navigation)
    Color m_color = { 255, 255, 0, 255 };   // The color of the agent (used for rendering, assumes raylib's Color structure)
    Agent* m_target = nullptr;  // Target agent that this agent might follow or interact with
};

