#include "Recognition.h"
#include "BasicGestures.h"
#include "Config.h"
#include "Utility.h"

//Recognition starts from activation gesture
//After that it recognize function
//Delay between changing fingers is constant
/**@return vector of recognized gestures*/
const std::vector<SimpleGesture> SimpleActionStateMachine::Recognize() const
{
    //Tuple used to avoid duplicating state array
    //Items would be removed in process of recognition
    //first index - index in states array of gestures
    //second index - index of the atomary action inside states array item
    std::vector<Tuple<int, int>> ResIndexes(States.size());
    std::vector<SimpleGesture> res{};

    //Starting pairs of indexes
    int Generator{};
    std::generate(ResIndexes.begin(), ResIndexes.end(), [&Generator](){return Tuple<int, int>{Generator++, 0};});

    Serial.println("-----Start recognition-----");
    while(!ResIndexes.empty() && res.empty())
    {
        Serial.println("---------Change gesture---------");
        my_delay(GESTURE_CHANGE_DELAY);
        FingersPosition CurrentState {readMedianValue(3, 200)};

        //Recognizing
        for(int i{}; i < ResIndexes.size(); ++i)
        {
            bool isActionsEquals{ActionsImpreciseComparsion(CurrentState, States[ResIndexes[i].first][ResIndexes[i].second])};

            Serial.println("Current ");
            printPositions(CurrentState);
            Serial.println();
            printPositions(States[ResIndexes[i].first][ResIndexes[i].second]);
            Serial.println();
            Serial.println(String(ResIndexes[i].first) + ", " + String(ResIndexes[i].second));
            Serial.println("Action equals: " + String((isActionsEquals ? "true" : "false")));
            Serial.println("In result: " + String(ResIndexes.size()));

            if(isActionsEquals)
            {
                //Increasing index of action
                ++ResIndexes[i].second;
                if(ResIndexes[i].second >= States[ResIndexes[i].first].size())
                {
                    res.push_back(States[ResIndexes[0].first]);
                    ResIndexes.erase(ResIndexes.begin() + ResIndexes[i].first);
                    --i;
                }
            }
            else
            {
                //Not recognized
                //Remove incompatible item
                Serial.println("--------Action not recognized--------");
                ResIndexes.erase(ResIndexes.begin() + ResIndexes[i].first);
                --i;
                Serial.println("*****ResIndexes len: " + String(ResIndexes.size()) + "*****");
            }
        }
    }
    Serial.println("Ended recognition\n");
    return res;
}

bool SimpleActionStateMachine::RecognizeActivation() const
{
    FingersPosition CurrentState {readMedianValue(3, 200)};
    bool isActionsEquals{ActionsImpreciseComparsion(CurrentState, ActivationGesture)};
    Serial.println("Current ");
    printPositions(CurrentState);
    Serial.println();
    printPositions(ActivationGesture);
    Serial.println();
    if(isActionsEquals)
    {
        Serial.println("--------Activation recognized--------");
        return true;
    }
        
    Serial.println("--------Activation not recognized--------");
    return false;
}

//If value in first object equals then there's problem with sensor and its value won't influence the result
bool ActionsImpreciseComparsion(FingersPosition st1, FingersPosition st2)
{
    return st1[0] == 0 ? true : std::max(st1[0],st2[0]) - std::min(st1[0],st2[0]) <= FIRST_FINGER_DELTA && 
           st1[1] == 0 ? true : std::max(st1[1],st2[1]) - std::min(st1[1],st2[1]) <= SECOND_FINGER_DELTA &&
           st1[2] == 0 ? true : std::max(st1[2],st2[2]) - std::min(st1[2],st2[2]) <= THIRD_FINGER_DELTA &&
           st1[3] == 0 ? true : std::max(st1[3],st2[3]) - std::min(st1[3],st2[3]) <= FOURTH_FINGER_DELTA &&
           st1[4] == 0 ? true : std::max(st1[4],st2[4]) - std::min(st1[4],st2[4]) <= FIFTH_FINGER_DELTA;
}