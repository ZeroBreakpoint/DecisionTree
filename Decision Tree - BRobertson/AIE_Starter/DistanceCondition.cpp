#include "DistanceCondition.h"

bool DistanceCondition::IsTrue(Agent* agent)
{
    // If the agent doesn't have a target, return false (no condition to evaluate).
    if (agent->GetTarget() == nullptr) return false;

    // Calculate the distance between the agent's position and its target's position.
    float distance = glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition());

    // Check if the condition is to be evaluated based on whether the distance is less than the threshold.
    if (m_lessThan) {
        return distance < m_distance; // Return true if the distance is less than the threshold.
    }
    else {
        return distance > m_distance;  // Return true if the distance is greater than the threshold.
    }
}