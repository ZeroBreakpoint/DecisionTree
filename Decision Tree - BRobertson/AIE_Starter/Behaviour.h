#pragma once
#include <glm/glm.hpp>
#include "raylib.h"


class Agent;  // Forward declaration of the Agent class

class Behaviour
{
	public:
		virtual void Update(Agent* agent, float deltaTime) = 0;  // Pure virtual function that updates the agent's state
		// Add this line to declare the Enter method as virtual

		// Virtual Enter method that can be overridden by specific behaviors
		virtual void Enter(Agent* agent) {}
};

