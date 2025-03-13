#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include "PathAgent.h"
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "Agent.h"
#include "Behaviour.h"
#include "GoToPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "DistanceCondition.h"
#include "DecisionTree.h"
#include "ActionNode.h"
#include "QuestionNode.h"
#include <cstdlib>
#include <ctime>

using namespace AIForGames;

int main(int argc, char* argv[])
{
    int screenWidth = 598;
    int screenHeight = 398;

    InitWindow(screenWidth, screenHeight, "Decision Tree - Assessment 4 - Bradley Robertson");

    SetTargetFPS(60);
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::vector<std::string> asciiMap = {
        "000000000000",
        "010111011100",
        "010101110110",
        "011100000010",
        "010111111110",
        "010000001000",
        "011111111110",
        "000000000000"
    };

    NodeMap nodeMap;
    nodeMap.Initialise(asciiMap, 50);

    // Create first agent with GoToPointBehaviour (player controlled)
    Agent agent1(&nodeMap, new GoToPointBehaviour());
    agent1.SetSpeed(64);
    agent1.SetColor({ 0, 255, 0, 255 });  // Set to green

    // Set the starting position of agent1 to a random node
    AIForGames::Node* randomStartNode = nodeMap.GetRandomNode();  // Get a random node from the map
    if (randomStartNode != nullptr) {
        agent1.SetNode(randomStartNode);  // Set agent1's starting node to the random node
    }
    else {
        std::cerr << "Error: Could not find a valid random starting node." << std::endl;
    }

    // Create second agent with WanderBehaviour (random movement)
    Agent agent2(&nodeMap, new WanderBehaviour());
    agent2.SetNode(nodeMap.GetRandomNode());  // Start at a random node
    agent2.SetSpeed(64);
    agent2.SetColor({ 0, 0, 255, 255 });  // Set to blue

    // Setup condition for the decision tree
    auto farFromAgent1 = std::make_shared<DistanceCondition>(90.0f, false);

    // Create action nodes for following and wandering
    auto followAction = std::make_shared<ActionNode>(new FollowBehaviour());
    auto wanderAction = std::make_shared<ActionNode>(new WanderBehaviour());  

    // Setup decision tree structure
    // Root node checks if agent is far from agent1 -> wander, else check if close -> follow
    auto rootNode = std::make_shared<QuestionNode>(farFromAgent1, wanderAction, followAction);

    
    Agent agent3(&nodeMap, nullptr);  // No initial behaviour assigned.
    agent3.SetNode(nodeMap.GetRandomNode());
    agent3.SetTarget(&agent1);  // Set Agent 3's target
    agent3.SetSpeed(32);

    // Create the decision tree
    DecisionTree decisionTree(rootNode);


    while (!WindowShouldClose())  // Loop until the user closes the window
    {
        float deltaTime = GetFrameTime();  // Get the time elapsed since the last frame

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();  // Draw the Node Map

        agent1.Update(deltaTime);
        agent1.Draw();   // Draw the first agent (Player Controlled)

        agent2.Update(deltaTime);
        agent2.Draw();   // Draw the second agent (Wandering)

        // Update and draw Agent 3 using the decision tree
        decisionTree.Update(&agent3, deltaTime);
        agent3.Update(deltaTime);
        agent3.Draw();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}