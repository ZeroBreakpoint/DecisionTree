#pragma once
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "raylib.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include <cfloat>

class PathAgent
{
private:
    glm::vec2 m_position{ 0.0f, 0.0f };  // The agent's current position in the world, initialized at (0,0).
    int m_currentIndex{ 0 };  // The index representing the current position in the path vector.
    AIForGames::Node* m_currentNode{ nullptr };  // Pointer to the current node that the agent is standing on or near.
    float m_speed{ 0.0f };  // Speed at which the agent moves between nodes.

public:
    const std::vector<AIForGames::Node*>& GetPath() const { return m_path; }   // Returns a const reference to the agent's path.
    std::vector<AIForGames::Node*> m_path;  // Vector storing the path the agent is following.
    void Update(float deltaTime);  // Updates the agent's position and path progress based on deltaTime.
    void GoToNode(AIForGames::Node* end, NodeMap& nodeMap);   // Initiates a movement to a specific node by calculating a path.
    void Draw() const;  // Draws the agent on the screen.
    void ClearPath();   // Clears the agent's current path.
    void SetNode(AIForGames::Node* node);  // Sets the agent's current node.
    void SetSpeed(float speed);  // Sets the agent's movement speed.
    glm::vec2 GetPosition() const { return m_position; }  // Returns the agent's current position.
 };

