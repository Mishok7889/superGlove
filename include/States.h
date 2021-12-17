#pragma once
#include <Arduino.h>
#include <vector>
#include <string>
#include <array>
#include <Utility.h>

//Set of sensor values in a moment of time
struct FingersPosition
{
public:
  inline FingersPosition(){}
  inline FingersPosition(const std::array<uint16_t, 5>& vals):fingers(vals){}
  inline uint16_t& operator[](int i){return fingers[i];};
  inline uint16_t operator[](int i) const{return fingers[i];};
private:
  std::array<uint16_t, 5> fingers;
};

class SimpleGesture
{
public:
  inline SimpleGesture():gestures(){}
  inline SimpleGesture(const std::vector<FingersPosition>& pos, uint16_t keycodeIn):gestures{pos}, keycode{keycodeIn}{}
  inline void add(const FingersPosition& pos) {gestures.push_back(pos);}
  inline FingersPosition& operator[](int i) {return gestures[i];}
  inline const FingersPosition operator[](int i) const {return gestures[i];}
  inline int size() const {return gestures.size();}
  inline uint16_t getCode() const {return keycode;}
private:
  std::vector<FingersPosition> gestures;
  uint16_t keycode;
};

void debugPrint();
void printPositions(const FingersPosition& fingers);
void printGesture(const SimpleGesture& gesture);

FingersPosition readFingersPosition();
SimpleGesture recordSimpleGesture(const int numberOfActions = 3, int numberOfMeasures = 3);
FingersPosition readMedianValue(const int numberOfMeasures = 3, const int readingDelay = 500);