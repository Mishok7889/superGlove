#include <Arduino.h>
#include "string.h"
#include "States.h"
#include "Config.h"
#include "Actions.h"
#include "BasicGestures.h"
#include "HID-Project.h"
#include "avr/wdt.h"

void setup()
{
  Serial.begin(9600);
  //Consumer keys: play, pause, etc
  Consumer.begin();
  //Avoid bootloop
  delay(1000);
  wdt_enable(WDTO_4S);
}

void loop()
{
  wdt_reset();
  if(StateMachine.RecognizeActivation())
  {
    std::vector<SimpleGesture> recognized{StateMachine.Recognize()};
    if(recognized.empty())
    {
      Serial.println("Not recognized");
    }
    else
    {
      PressConsumerKeyHIDAction(static_cast<ConsumerKeycode>((*recognized.begin()).getCode())).doAction();
    }
  }
}

