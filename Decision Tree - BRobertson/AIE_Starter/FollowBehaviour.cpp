#include "FollowBehaviour.h"

using namespace AIForGames;

// Update function is called every frame to update the agent's behavior and make it follow its target.
void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
    Agent* target = agent->GetTarget();
    if (target)
    {
        glm::vec2 targetPosition = target->GetPosition();
        AIForGames::Node* closestNode = agent->GetNodeMap()->GetClosestNode(targetPosition);

        if (closestNode != nullptr) {
            const std::vector<AIForGames::Node*>& path = agent->GetPathAgent().GetPath();

            if (path.empty() || closestNode != path.back()) {
                agent->GoTo(closestNode->position);
            }
        }

        // Ensure path agent is being updated
        agent->GetPathAgent().Update(deltaTime);
    }
}

void FollowBehaviour::Enter(Agent* agent)
{
    // Red when following
    agent->SetColor({ 255, 0, 0, 255 });

    // Reset the agent's path, clearing any previous movement commands or pathfinding data.
    agent->Reset();  
}