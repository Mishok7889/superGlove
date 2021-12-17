#include "BasicGestures.h"
#include "HID-Project.h"

const SimpleActionStateMachine StateMachine
{
    std::vector<SimpleGesture>
    {
        //Ok, first finger, palm, first and last finger, 
        SimpleGesture(
            std::vector<FingersPosition>
            {
                std::array<uint16_t, 5>{37,25,31,19,2},
                std::array<uint16_t, 5>{37,19,25,13,0},
                std::array<uint16_t, 5>{13,0,12,4,0},
                std::array<uint16_t, 5>{41,21,19,12,4}
            },
            ConsumerKeycode::MEDIA_NEXT
        ),
        // Ok, palm, O 
        SimpleGesture(
            std::vector<FingersPosition>
            {
                std::array<uint16_t, 5>{34,21,29,19,0},
                std::array<uint16_t, 5>{22,13,17,4,0},
                std::array<uint16_t, 5>{36,25,14,5,0},
            },
            ConsumerKeycode::MEDIA_PLAY_PAUSE
        ),
        //Ok, palm, goat
        SimpleGesture(
            std::vector<FingersPosition>
            {
                std::array<uint16_t, 5>{54,38,41,11,19},
                std::array<uint16_t, 5>{40,20,41,7,17},
                std::array<uint16_t, 5>{15,11,16,6,9},
                std::array<uint16_t, 5>{39,27,33,19,14}
            },
            ConsumerKeycode::MEDIA_PREVIOUS
        )
    }
};

const FingersPosition ActivationGesture{std::array<uint16_t, 5>{68,30,41,28,28}};