#pragma once
#include <Arduino.h>
#include <vector>
#include <valarray>
#include <string>
#include "Config.h"

//Atomary action is a set of sensor values in a period of time
struct AtomaryAction
{
  float firstFinger;
  float secondFinger;
  float thirdFinger;
  float fourthFinger;
  float fifthFinger;

  AtomaryAction& operator+=(const AtomaryAction& Action);
};

//Gesture is a sequence of atomary actions
class Gesture
{
public:
  inline Gesture():Actions(0){}
  inline Gesture(std::valarray<AtomaryAction> GestureActions):Actions(GestureActions){}
  inline Gesture(int Length):Actions(Length){}
  inline AtomaryAction& operator[](int Index){return Actions[Index];}
  inline const AtomaryAction& operator[] (int Index) const{return Actions[Index];}
  inline int size() const {return Actions.size();}
private:
    std::valarray<AtomaryAction> Actions;
};
//Used to compare atomary actions with some delta
bool ActionsImpreciseComparsion(const AtomaryAction& Action1, const AtomaryAction& Action2);
Gesture makeGesture(int ActionsNumber, int BetweenActionsDelay = GESTURE_CHANGE_DELAY);


void printAction(const AtomaryAction& Action);
void printGesture(const Gesture& Gesture);

inline float readAngle(const int pin, const int min, const int max)
{
  return map(constrain(analogRead(pin), min, max), min, max, 0, 90); 
}

AtomaryAction GetCurrentState();