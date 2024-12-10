#include "ActionNode.h"

void ActionNode::Execute(Agent* agent, float deltaTime)
{
    if (m_behaviour)
    {
        if (agent->GetBehaviour() != m_behaviour)
        {
            // Change the behavior only if it's different
            agent->SetBehaviour(m_behaviour);
            m_behaviour->Enter(agent);
        }
    }
}