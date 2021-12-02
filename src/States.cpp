#include "Utility.h"
#include "States.h"

inline bool FingerInRange(double RawValue, double NeededValue ,double Delta = FINGER_RECOGNITION_VALUE_DELTA)
{
    return RawValue < NeededValue + Delta && RawValue > NeededValue - Delta;
}

bool ActionsImpreciseComparsion(const AtomaryAction& Action1, const AtomaryAction& Action2)
{
    return FingerInRange(Action1.firstFinger, Action2.firstFinger) && 
           FingerInRange(Action1.secondFinger, Action2.secondFinger) && 
           FingerInRange(Action1.thirdFinger, Action2.thirdFinger) && 
           FingerInRange(Action1.fourthFinger, Action2.fourthFinger) && 
           FingerInRange(Action1.fifthFinger, Action2.fifthFinger);
}

AtomaryAction& AtomaryAction::operator+=(const AtomaryAction& action)
{
    firstFinger += action.firstFinger;
    secondFinger += action.secondFinger;
    thirdFinger += action.thirdFinger;
    fourthFinger += action.fourthFinger;
    fifthFinger += action.fifthFinger;
}

//Recognition starts from activation gesture
//After that it recognize function
//Delay between changing fingers is constant
/**@return vector of recognized gestures*/
const std::vector<Gesture> StateMachine::Recognize() const
{
    //Tuple used to avoid duplicating state array
    //Items would be removed in process of recognition
    //First index - index in states array of gestures
    //Second index - index of the atomary action inside states array item
    std::vector<Tuple<int, int>> ResIndexes(States.size());
    std::vector<Gesture> Res{};

    //Starting pairs of indexes
    int Generator{};
    std::generate(ResIndexes.begin(), ResIndexes.end(), [&Generator](){return Tuple<int, int>{Generator++, 0};});

    Serial.println("-----Start recognition-----");
    while(!ResIndexes.empty() && Res.empty())
    {
        Serial.println("---------Change gesture---------");
        delay(GESTURE_CHANGE_DELAY);
        AtomaryAction CurrentState {GetCurrentState()};
        
        //Recognizing
        for(int i{}; i < ResIndexes.size(); ++i)
        {
            bool isActionsEquals{ActionsImpreciseComparsion(CurrentState, States[ResIndexes[i].First][ResIndexes[i].Second])};

            Serial.println("Current ");
            printAction(CurrentState);
            printAction(States[ResIndexes[i].First][ResIndexes[i].Second]);
            Serial.println(String(ResIndexes[i].First) + ", " + String(ResIndexes[i].Second));
            Serial.println("Action equals: " + String((isActionsEquals ? "true" : "false")));
            Serial.println("In result: " + String(ResIndexes.size()));

            if(isActionsEquals)
            {
                //Increasing index of action
                ++ResIndexes[i].Second;
                if(ResIndexes[i].Second >= States[ResIndexes[i].First].size())
                {
                    Res.push_back(States[ResIndexes[0].First]);
                    ResIndexes.erase(ResIndexes.begin() + ResIndexes[i].First);
                    --i;
                }
            }
            else
            {
                //Not recognized
                //Remove incompatible item
                Serial.println("--------Action not recognized--------");
                ResIndexes.erase(ResIndexes.begin() + ResIndexes[i].First);
                --i;
            }
        }
    }
    Serial.println("Ended recognition");
    return Res;
}

Gesture makeGesture(int ActionsNumber,int BetweenActionsDelay)
{
    Gesture Res{ActionsNumber};
    for(int i{0}; i < ActionsNumber; ++i)
    {
        Serial.println("Recognizing action: " + String(i));
        Res[i] = GetCurrentState();
        delay(2000);
    }
    return Res;
}

AtomaryAction GetCurrentState()
{
  AtomaryAction res{};
//   res.firstFinger = readAngle(FIRST_FINGER_PIN, FIRST_FINGER_MIN, FIRST_FINGER_MAX);
//   res.secondFinger = readAngle(SECOND_FINGER_PIN, SECOND_FINGER_MIN, SECOND_FINGER_MAX);
//   res.thirdFinger = readAngle(THIRD_FINGER_PIN, THIRD_FINGER_MIN, THIRD_FINGER_MAX);
//   res.fourthFinger = readAngle(FOURTH_FINGER_PIN, FOURTH_FINGER_MIN, FOURTH_FINGER_MAX);
//   res.fifthFinger = readAngle(FIFTH_FINGER_PIN, FIFTH_FINGER_MIN, FIFTH_FINGER_MAX);

  res.firstFinger = analogRead(FIRST_FINGER_PIN);
  res.secondFinger = analogRead(SECOND_FINGER_PIN);
  res.thirdFinger = analogRead(THIRD_FINGER_PIN);
  res.fourthFinger = analogRead(FOURTH_FINGER_PIN);
  res.fifthFinger = analogRead(FIFTH_FINGER_PIN);
  return res;
}

void printAction(const AtomaryAction& Action)
{
                    Serial.println("Action: "       + String(Action.firstFinger , 2)+
                                                ", " + String(Action.secondFinger , 2)+ 
                                                ", " + String(Action.thirdFinger , 2)+ 
                                                ", " + String(Action.fourthFinger , 2)+ 
                                                ", " + String(Action.fifthFinger, 2));
}

void printGesture(const Gesture& Gesture)
{
    for(int i{0}; i < Gesture.size(); ++i)
    {
        Serial.println("Action: " + String(i) + " " + Gesture[i].firstFinger + 
                                              " " + Gesture[i].secondFinger + 
                                              " " + Gesture[i].thirdFinger + 
                                              " " + Gesture[i].fourthFinger + 
                                              " " + Gesture[i].fifthFinger);
    }
}