#include "Recognition.h"

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

bool ActionsImpreciseComparsion(const AtomaryAction& Action1, const AtomaryAction& Action2)
{
    return FingerInRange(Action1.firstFinger, Action2.firstFinger) && 
           FingerInRange(Action1.secondFinger, Action2.secondFinger) && 
           FingerInRange(Action1.thirdFinger, Action2.thirdFinger) && 
           FingerInRange(Action1.fourthFinger, Action2.fourthFinger) && 
           FingerInRange(Action1.fifthFinger, Action2.fifthFinger);
}
