#pragma once
#include "Behaviour.h"
#include "Agent.h"

class SelectorBehaviour : public Behaviour
{
private:
    Behaviour* m_b1;  // Pointer to the first behaviour option.
    Behaviour* m_b2;  // Pointer to the second behaviour option.
    Behaviour* m_selected;  // Pointer to the currently selected behaviour.

public:
    SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2), m_selected(nullptr){}  // Constructor that initializes the two behaviours and sets the selected behaviour to nullptr.
    virtual void Update(Agent* agent, float deltaTime);   // Override of the Update function, which updates the selected behaviour based on the agent's state and deltaTime.

    ~SelectorBehaviour();  // Destructor for cleaning up resources (if needed).
    void SetBehaviour(Behaviour* b, Agent* agent);  // Function to set the current behaviour dynamically, updating the agent's behaviour.
};

