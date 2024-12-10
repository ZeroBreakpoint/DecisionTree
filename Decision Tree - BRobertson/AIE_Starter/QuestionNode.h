#pragma once
#include <memory>
#include "Condition.h"
#include "Decision.h"

class QuestionNode : public Decision
{
private:
    std::shared_ptr<Condition> m_condition;   // Condition to evaluate
    std::shared_ptr<Decision> m_trueBranch;   // Decision if the condition is true
    std::shared_ptr<Decision> m_falseBranch;  // Decision if the condition is false

public:
    // Constructor taking shared_ptr for condition, trueBranch, and falseBranch
    QuestionNode(std::shared_ptr<Condition> condition, std::shared_ptr<Decision> trueBranch, std::shared_ptr<Decision> falseBranch)
        : m_condition(condition), m_trueBranch(trueBranch), m_falseBranch(falseBranch) {}

    virtual ~QuestionNode() = default;

    // Execute the decision based on the condition
    void Execute(Agent* agent, float deltaTime) override
    {
        if (m_condition->IsTrue(agent)) {
            if (m_trueBranch) {
                m_trueBranch->Execute(agent, deltaTime);
            }
        }
        else {
            if (m_falseBranch) {
                m_falseBranch->Execute(agent, deltaTime);
            }
        }
    }
};