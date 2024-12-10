#pragma once
#include <memory>
#include "Decision.h"

class DecisionTree
{
private:
    std::shared_ptr<Decision> m_rootDecision;  // Use shared_ptr for root decision

public:
    DecisionTree(std::shared_ptr<Decision> root) : m_rootDecision(root) {}

    virtual ~DecisionTree() = default;

    // Update function that calls the root decision's execute method
    void Update(Agent* agent, float deltaTime)
    {
        if (m_rootDecision)
            m_rootDecision->Execute(agent, deltaTime);
    }
};