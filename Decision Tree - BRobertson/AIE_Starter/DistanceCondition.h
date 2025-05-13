#pragma once

class Condition
{
public:
    virtual bool IsTrue(Agent* agent) = 0;
};

class DistanceCondition : public Condition
{
private:
    float m_distance;  // The distance threshold to evaluate
    bool m_lessThan;  // Flag to determine if the condition checks for less than or greater than the distance

public:
    DistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}  // Constructor to initialise distance and comparison type
    virtual bool IsTrue(Agent* agent);   // Override of the IsTrue method to evaluate the condition based on the agent's state
};

