#pragma once
#include "Behaviour.h"
#include "Pathfinding.h"
#include "State.h"
#include <vector>
#include <glm/glm.hpp>

class State;  // Forward declaration of State


class FiniteStateMachine : public Behaviour
{
private:
    std::vector<State*> m_states;  // Vector to store all the states
    State* m_currentState;  // Pointer to the current active state

public:
    FiniteStateMachine(State* initialState) : m_currentState(initialState) {}   // Constructor initializes the current state

    virtual ~FiniteStateMachine();

    void AddState(State* state) {m_states.push_back(state);}  // Method to add a state to the FSM

    void Update(Agent* agent, float deltaTime);  // Method to update the FSM

    void Enter(Agent* agent);  // Method to enter the current state
};
