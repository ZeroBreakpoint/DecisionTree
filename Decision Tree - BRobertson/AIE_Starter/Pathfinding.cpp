#include "Pathfinding.h"

using namespace AIForGames;

// Connects the current node to another node by creating an edge with the specified cost.  This edge is added to the list of connections for the current node.
void AIForGames::Node::ConnectTo(Node* other, float cost)
{

	// Add a new edge to the 'connections' list, linking this node to the 'other' node.  The 'cost' represents the weight of traveling from this node to the 'other' node.
	connections.push_back(Edge(other, cost));
}
