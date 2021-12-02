#pragma once
#include "Arduino.h" //It is needed to make hid-project work
#include "stdint.h"
#include "HID-Project.h"

class Action
{
  virtual void doAction() = 0;
};

//Action for sending one Consumer key signal
class PressConsumerKeyHIDAction : public Action
{
public:
  PressConsumerKeyHIDAction(ConsumerKeycode keycodeIn);
  virtual void doAction() override;
private:
  ConsumerKeycode keycode;
};

//Action for sending one Consumer key signal
class PressKeyboardKeyHIDAction : public Action
{
public:
  PressKeyboardKeyHIDAction(KeyboardKeycode keycodeIn);
  virtual void doAction() override;
private:
  KeyboardKeycode keycode;
};