#pragma once
#include "States.h"

//State machine is used to store gesture which could be recognized
//It allows to recognize gesture
class SimpleActionStateMachine
{
public:
    const std::vector<SimpleGesture> Recognize() const;
// private:
    std::vector<SimpleGesture> States;
};