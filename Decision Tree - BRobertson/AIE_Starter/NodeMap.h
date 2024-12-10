#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include "Pathfinding.h"
#include <raylib.h>

class NodeMap
{
    int m_width, m_height;
    float m_cellSize;
    AIForGames::Node** m_nodes;

public:
    NodeMap();  // Constructor to initialize the NodeMap object.
    ~NodeMap();  // Destructor to clean up memory used by the NodeMap.
    AIForGames::Node* GetNode(int x, int y);  // Returns the node located at the (x, y) position in the node grid.
    void Initialise(std::vector<std::string> asciiMap, int cellSize);   // Initialises the node map based on an ASCII map and assigns cell size. 
    void Draw();  // Draws the node map to the screen using Raylib's rendering functions.
    std::vector<AIForGames::Node*> DijkstrasSearch(glm::vec2 startPos, AIForGames::Node* endNode);  // Returns the resulting path as a vector of nodes.
    void DrawPath(const std::vector<AIForGames::Node*>& path, Color lineColor);   // Draws the path, given as a vector of nodes, on the screen using a specific color.
    AIForGames::Node* GetClosestNode(glm::vec2 worldPos);  // Returns the closest node to a given world position (x, y coordinates in the world space).
    AIForGames::Node* GetRandomNode();  // Returns a randomly selected node from the node map.
    float GetCellSize() const { return m_cellSize; }  // Getter for cell size.
    int GetWidth() const { return m_width; }  // Getter for the width of the map (number of nodes horizontally).
    int GetHeight() const { return m_height; }  // Getter for the height of the map (number of nodes vertically).
};