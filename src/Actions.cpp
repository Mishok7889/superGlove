#include "Actions.h"

PressConsumerKeyHIDAction::PressConsumerKeyHIDAction(ConsumerKeycode keycodeIn) 
        : keycode{keycodeIn}{}

void PressConsumerKeyHIDAction::doAction()
{
    Serial.println("Executed action: " + String(keycode));
    Consumer.write(keycode);
}

PressKeyboardKeyHIDAction::PressKeyboardKeyHIDAction(KeyboardKeycode keycodeIn) 
        : keycode{keycodeIn}{}

void PressKeyboardKeyHIDAction::doAction()
{
    Serial.println("Executed action: " + String(keycode));
    Keyboard.write(keycode);
}