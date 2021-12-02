#include <Arduino.h>
#include "string.h"
#include "Recognition.h"
#include "Config.h"
#include "HID-Project.h"

void debugPrint()
{
  uint16_t a1{};
  uint16_t a2{};
  uint16_t a3{};
  uint16_t a4{};
  uint16_t a5{};
  for(int i{0}; i < 200; ++i)
  {
      a1 += analogRead(FIRST_FINGER_PIN);
      a2 += analogRead(SECOND_FINGER_PIN);
      a3 += analogRead(THIRD_FINGER_PIN);
      a4 += analogRead(FOURTH_FINGER_PIN);
      a5 += analogRead(FIFTH_FINGER_PIN);
      delay(10);
  }
  a1 /= 200;
  a2 /= 200;
  a3 /= 200;
  a4 /= 200;
  a5 /= 200;
  Serial.print(a1);
  Serial.print('\t');
  Serial.print(a2);
  Serial.print('\t');
  Serial.print(a3);
  Serial.print('\t');
  Serial.print(a4);
  Serial.print('\t');
  Serial.print(a5);
  Serial.print('\n');
}

void recognition()
{

}



//This function just print out sequence of gesture
//TODO:  write into memory
Gesture recordGesture(int numberOfActions/*, uint16_t numberOfMeasures = 3*/)
{
  uint16_t numberOfMeasures{3};
  
  std::valarray<AtomaryAction> resActions(numberOfActions);

  Serial.println("Prepare for recognition");
  delay(3000);
  for(int i{0}; i < numberOfActions; ++i)
  {
    Serial.println("Recognizing " + String(i) + " gesture\n");
    Serial.println("Start in 1 second");
    delay(1000);

    //Recognizing makes three measurements and compute average value
    //TODO: add check if the saved gestures are what user wanted to
    //      Just recognize them
    Serial.println("Started\n Hold your hand still\n");
    delay(3000);
    AtomaryAction accum{};
    for(int j{numberOfMeasures}; j > 0; --j)
    {
      Serial.println("Recognizing " + String(j));
      delay(1000);
      accum += GetCurrentState();
    }

    //There find median
    resActions[i] = {accum.firstFinger / numberOfMeasures,
                     accum.secondFinger / numberOfMeasures,
                     accum.thirdFinger / numberOfMeasures,
                     accum.fourthFinger / numberOfMeasures, 
                     accum.fifthFinger / numberOfMeasures};
    
    Serial.println("Recognized action\n");
    printAction(resActions[i]);
  }

  Gesture res{resActions};
  return res;
}

void setup()
{
  Serial.begin(9600);
  //Consumer keys: play, pause, etc
  Consumer.begin();
}

StateMachine ma{};

void loop()
{
  // debugPrint();

  //printGesture(recordGesture(3));
  //return;
  ma.States = std::vector<Gesture>();
  auto Gest{Gesture{3}};
  Gest[0] = (AtomaryAction{256, 16, 24, 12, 5});
  Gest[1] = (AtomaryAction{295, 15, 43, 26, 17});
  Gest[2] = (AtomaryAction{259, 30, 40, 23, 2});
  ma.States.push_back(Gest);

  std::vector<Gesture> recognitionResult{ma.Recognize()};
  if(!recognitionResult.empty())
  {
    Serial.println("+++++++++Success+++++++++");
    printGesture(recognitionResult[0]);
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  else
  {
    Serial.println("Cannot recognize");
    Serial.println("----------------\n----------------");
  }


  // printGesture(makeGesture(5, 500));
  // printGesture(ma.Recognize()[0]);
  delay(1000);
}