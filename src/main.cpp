#include <Arduino.h>
#include "string.h"
#include "States.h"
#include "Config.h"
#include "HID-Project.h"

void setup()
{
  Serial.begin(9600);
  //Consumer keys: play, pause, etc
  Consumer.begin();
}

void loop()
{
  // debugPrint();

  printGesture(recordSimpleGesture());
  delay(500);
}