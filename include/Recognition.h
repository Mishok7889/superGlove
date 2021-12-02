#pragma once
#include "States.h"

//State machine is used to store gesture which could be recognized
//It allows to recognize gesture
class StateMachine
{
public:
    const std::vector<Gesture> Recognize() const;
// private:
    std::vector<Gesture> States;
};


bool ActionsImpreciseComparsion(const AtomaryAction& Action1, const AtomaryAction& Action2);