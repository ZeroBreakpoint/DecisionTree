#include <glm/glm.hpp>
#include "NodeMap.h"
#include "Pathfinding.h"
#include <iostream>
#include <algorithm>
#include <cfloat>
#include "raylib.h"

using namespace AIForGames;

// Constructor definition (with member initialisations)
NodeMap::NodeMap() : m_width(0), m_height(0), m_cellSize(0), m_nodes(nullptr) {}

NodeMap::~NodeMap() {
    if (m_nodes) {
        for (int i = 0; i < m_width * m_height; i++) {
            delete m_nodes[i];  // Correctly delete each node pointer
        }
        delete[] m_nodes;  // Correctly delete the array of pointers
    }
}

void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
    m_cellSize = static_cast<float>(cellSize);  // Initialise m_cellSize
    const char emptySquare = '0';

    // assume all strings are the same length, so we'll size the map according
    // to the number of strings and the length of the first one
    m_height = static_cast<int>(asciiMap.size());
    m_width = static_cast<int>(asciiMap[0].size());

    m_nodes = new Node * [m_width * m_height];  // Initialise m_nodes

    // loop over the strings, creating Node entries as we go
    for (int y = 0; y < m_height; y++)
    {
        std::string& line = asciiMap[y];

        for (int x = 0; x < m_width; x++)
        {
            // get the x-th character, or return an empty node if the string         
            // isn't long enough
            char tile = x < line.size() ? line[x] : emptySquare;

            // create a node for anything but a '0' character
            m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
                : new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
        }
    }
    // Connect nodes to their neighbors (west and south)
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node)
            {
                // see if there's a node to our west, checking for array overruns      
                // first if we're on the west-most edge
                Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                if (nodeWest)
                {
                    node->ConnectTo(nodeWest, 1); // TODO weights
                    nodeWest->ConnectTo(node, 1);
                }

                // see if there's a node south of us, checking for array index
                // overruns again
                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, 1);
                    nodeSouth->ConnectTo(node, 1);
                }
            }
        }
    }
}

// Return the node at a given grid position, or nullptr if out of bounds
Node* NodeMap::GetNode(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return nullptr;
    return m_nodes[x + m_width * y];
}

void NodeMap::Draw()
{
    // Red color for the blocks
    Color cellColor{ 255, 0, 0, 255 };
    Color lineColor{ 128, 128, 128, 255 };

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                // Fix for conversion warning: cast float to int explicitly
                DrawRectangle(static_cast<int>(x * m_cellSize), static_cast<int>(y * m_cellSize),
                    static_cast<int>(m_cellSize - 1), static_cast<int>(m_cellSize - 1), cellColor);
            }
            else
            {
                // Draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    // Fix for conversion warning: cast float to int explicitly
                    DrawLine(static_cast<int>(node->position.x), static_cast<int>(node->position.y),
                        static_cast<int>(other->position.x), static_cast<int>(other->position.y),
                        lineColor);
                }
            }
        }
    }
}

// Helper function to return the sign of a value (-1, 0, or 1)
static int Sign(int input)
{
    if (input == 0) { return 0; }
    else if (input < 0) { return -1; }
    else { return 1; }
}

// Dijkstra's search algorithm to find the shortest path between two nodes
std::vector<Node*> NodeMap::DijkstrasSearch(glm::vec2 startPos, Node* endNode)
{
    Node* startNode = GetClosestNode(startPos);
 
    if (startNode == nullptr || endNode == nullptr)
    {
       return std::vector<Node*>(); // Validate the input and throw error if start or end node are null
    }
    if (startNode == endNode)
    {
        return std::vector<Node*>(); // Return an empty path if start and end nodes are the same
    }
    startNode->gScore = 0;
    startNode->previous = nullptr;
    std::vector<Node*> openList;
    std::vector<Node*> closedList;
    openList.push_back(startNode);
    while (!openList.empty()) {
        // Sort openList by Node.gScore
        std::sort(openList.begin(), openList.end(), [](Node* a, Node* b) {
            return a->gScore < b->gScore;
            });
        // Let currentNode = first item in openList
        Node* currentNode = openList.front();
        // If we visit the endNode, then we can exit early
        if (currentNode == endNode) {
            break;
        }
        // Remove currentNode from openList and add it to closedList
        openList.erase(openList.begin());
        closedList.push_back(currentNode);
        // For all connections in currentNode
        for (Edge& connection : currentNode->connections) {
            Node* targetNode = connection.target;
            // If targetNode is not in closedList
            if (std::find(closedList.begin(), closedList.end(), targetNode) == closedList.end()) {
                float gScore = currentNode->gScore + connection.cost;
                // If targetNode not in openList
                if (std::find(openList.begin(), openList.end(), targetNode) == openList.end()) {
                    targetNode->gScore = gScore;
                    targetNode->previous = currentNode;
                    openList.push_back(targetNode);
                }
                // Else if a shorter path to targetNode has been found
                else if (gScore < targetNode->gScore) {
                    targetNode->gScore = gScore;
                    targetNode->previous = currentNode;
                }
            }
        }
    }
    // Create Path in reverse from endNode to startNode
    std::vector<Node*> path;
    Node* currentNode = endNode;
    while (currentNode != nullptr) {
        path.insert(path.begin(), currentNode); // Add currentNode to the beginning of the path
        currentNode = currentNode->previous;
    }

    //Get the x and y directions (can be 1, 0, or -1) from the start node's position to the exact position of the agent. Let them be d1x and d1y respectively.
    int d1x = Sign(static_cast<int>(startPos.x - path[0]->position.x));
    int d1y = Sign(static_cast<int>(startPos.y - path[0]->position.y));

    //Get the x and y directions (can be 1, 0, or -1) from the start node's position to the position of the next node in the path. Let them be d2x and d2y respectively.
    int d2x = Sign(static_cast<int>(path[1]->position.x - path[0]->position.x));
    int d2y = Sign(static_cast<int>(path[1]->position.y - path[0]->position.y));

    if ((d1x == d2x) && (d1y == d2y)) { path.erase(path.begin()); } //Remove the first node if it goes backwards.

    return path; // Return the path for navigation between startNode and endNode
}

void NodeMap::DrawPath(const std::vector<Node*>& path, Color lineColor)
{
    // Iterate through the path, drawing lines between consecutive nodes
    for (size_t i = 1; i < path.size(); i++) {
        Node* nodeA = path[i - 1];
        Node* nodeB = path[i];

    // Draw a line between nodeA and nodeB
    DrawLine(
            static_cast<int>(nodeA->position.x),
            static_cast<int>(nodeA->position.y),
            static_cast<int>(nodeB->position.x),
            static_cast<int>(nodeB->position.y),
            lineColor
        );
    }
}

// Find the closest node to the start position
Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
    int i = static_cast<int>(worldPos.x / m_cellSize);
    int j = static_cast<int>(worldPos.y / m_cellSize);

    if (i < 0 || i >= m_width || j < 0 || j >= m_height) {
        std::cerr << "Error: Clicked position is out of bounds.  World Position: (" << worldPos.x << ", " << worldPos.y << ")" << std::endl; 
        return nullptr;
    }

    Node* node = GetNode(i, j);
    if (node == nullptr) {
        std::cerr << "Error: Closest node is null. No valid node at this position." << "Grid Position: (" << i << ", " << j << ")" << std::endl;
    }

    return node;
}

// Get a random node from the node map
AIForGames::Node* NodeMap::GetRandomNode()
{
    // Keep generating random coordinates until a valid node is found
    AIForGames::Node* node = nullptr;
    while (node == nullptr)
    {
        int x = rand() % m_width;
        int y = rand() % m_height;
        node = GetNode(x, y);
    }
    return node;  // Return a random valid node
}




