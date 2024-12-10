#include "FiniteStateMachine.h"
#include "State.h"

// Destructor for the FiniteStateMachine class.  It ensures that all dynamically allocated states are properly deleted when the FSM is destroyed.
FiniteStateMachine::~FiniteStateMachine()
{
    // Loop through all states stored in the FSM and delete them to free memory.
    for (State* state : m_states)
    {
        delete state;  // Clean up each state
    }
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
    State* newState = nullptr;

    // Check for transitions in the current state
    for (const State::Transition& transition : m_currentState->GetTransitions())
    {
        if (transition.condition->IsTrue(agent))
        {
            newState = transition.targetState;
            break;  // If a transition condition is met, break out of the loop
        }
    }

    // If a new state is found, transition to the new state
    if (newState != nullptr && newState != m_currentState)
    {
        m_currentState->Exit(agent);      // Exit the current state
        m_currentState = newState;        // Change to the new state
        m_currentState->Enter(agent);     // Enter the new state (this will change color)
    }

    // Update the current state
    m_currentState->Update(agent, deltaTime);
}

// Enter function is called when the FSM starts.  It ensures that the initial state of the FSM is properly initialized and executed.
void FiniteStateMachine::Enter(Agent* agent)
{
    // If a current state exists, call its Enter function to initialize the state.
    if (m_currentState)
    {
        m_currentState->Enter(agent);
    }
}