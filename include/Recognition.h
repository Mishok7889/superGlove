#pragma once
#include "States.h"

//State machine is used to store gesture which could be recognized
//It allows to recognize gesture
class SimpleActionStateMachine
{
public:
    const std::vector<SimpleGesture> Recognize() const;
    bool RecognizeActivation() const;
// private:
    std::vector<SimpleGesture> States;
};

bool ActionsImpreciseComparsion(FingersPosition st1, FingersPosition st2);