#include "WanderBehaviour.h"
#include <cstdlib>
#include <ctime>

using namespace AIForGames;

// Update function is called every frame to handle the agent's wandering behavior.
void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
    // Check if the agent has completed its current path
    if (agent->PathComplete()) {
        // If the path is complete, choose a random node from the node map
        AIForGames::Node* randomNode = agent->GetNodeMap()->GetRandomNode();
        // Command the agent to go to the randomly selected node
        agent->GoToNode(randomNode);
    }

    // Update the agent's path-following logic based on the time elapsed (deltaTime)
    agent->GetPathAgent().Update(deltaTime);
}

// Enter function is called when the agent transitions into the wander behavior.
void WanderBehaviour::Enter(Agent* agent)
{
    // Yellow when wandering
    agent->SetColor({ 255, 255, 0, 255 });

    // Reset the agent's path to ensure it starts fresh when entering the wander state
    agent->Reset();
}