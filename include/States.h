#pragma once
#include <Arduino.h>
#include <vector>
#include <string>
#include <Utility.h>
#include "Config.h"
#include "HID-Project.h"

//Set of sensor values in a moment of time
struct FingersPosition
{
public:
  inline uint16_t& operator[](int i){return fingers[i];};
  inline uint16_t operator[](int i) const{return fingers[i];};
private:
  uint16_t fingers[5];
};

class SimpleGesture
{
public:
  inline void add(const FingersPosition& pos) {gestures.push_back(pos);}
  inline FingersPosition& operator[](int i) {return gestures[i];}
  inline const FingersPosition operator[](int i) const {return gestures[i];}
  inline int size() const {return gestures.size();}
private:
  std::vector<FingersPosition> gestures;
};

void debugPrint();
void printPositions(const FingersPosition& fingers);
void printGesture(const SimpleGesture& gesture);

FingersPosition readFingersPosition();
SimpleGesture recordSimpleGesture(const int numberOfActions = 3, int numberOfMeasures = 3);