#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <raylib.h>
#include <cfloat>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Node* target;  // Pointer to the target node connected by this edge.
        float cost;  // The cost to travel to the target node (used in pathfinding algorithms).
        Edge() : target(nullptr), cost(0) {}  // Default constructor initializes target to nullptr and cost to 0.
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}   // Constructor that initializes an edge with a target node and a given cost.
    };

    struct Node {
        glm::vec2 position;  // The 2D position of the node in space.
        std::vector<Edge> connections;  // A list of edges that connect this node to other nodes.
        float gScore;  // The cost to reach this node from the start node (used in pathfinding algorithms).
        Node* previous;  // Pointer to the previous node in the path (used for reconstructing the path).
        Node() : position(0.0f, 0.0f), gScore(FLT_MAX), previous(nullptr) {}   // Default constructor initializes position to (0, 0), gScore to maximum possible value, and previous to nullptr.
        Node(float x, float y) : position(x, y), gScore(FLT_MAX), previous(nullptr) {}  // Constructor that specifies the position of the node.
        void ConnectTo(Node* other, float cost);   // Connect this node to another node by creating an edge with a specific cost.
    };
}
