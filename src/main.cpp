#include <Arduino.h>
#include "string.h"
#include "States.h"
#include "Config.h"
#include "Actions.h"

void setup()
{
  Serial.begin(9600);
  //Consumer keys: play, pause, etc
  Consumer.begin();
}

void loop()
{
  // debugPrint();

  // printGesture(recordSimpleGesture());
  PressConsumerKeyHIDAction(ConsumerKeycode::MEDIA_PLAY_PAUSE).doAction();
  delay(5000);
}