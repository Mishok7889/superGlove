#pragma once
#include "Arduino.h"
constexpr byte FIRST_FINGER_PIN{A1};
constexpr byte FIRST_FINGER_MAX{375};
constexpr byte FIRST_FINGER_MIN{0};
constexpr byte FIRST_FINGER_DELTA{( FIRST_FINGER_MAX -  FIRST_FINGER_MIN)* .1};

constexpr byte SECOND_FINGER_PIN{A3};
constexpr byte SECOND_FINGER_MAX{50};
constexpr byte SECOND_FINGER_MIN{0};
constexpr byte SECOND_FINGER_DELTA{(SECOND_FINGER_MAX - SECOND_FINGER_MIN)* .1};

constexpr byte THIRD_FINGER_PIN{A2};
constexpr byte THIRD_FINGER_MAX{50};
constexpr byte THIRD_FINGER_MIN{0};
constexpr byte THIRD_FINGER_DELTA{( THIRD_FINGER_MAX -  THIRD_FINGER_MIN)* .1};

constexpr byte FOURTH_FINGER_PIN{A0};
constexpr byte FOURTH_FINGER_MAX{50};
constexpr byte FOURTH_FINGER_MIN{0};
constexpr byte FOURTH_FINGER_DELTA{(FOURTH_FINGER_MAX - FOURTH_FINGER_MIN)* .1};

constexpr byte FIFTH_FINGER_PIN{A8};
constexpr byte FIFTH_FINGER_MAX{50};
constexpr byte FIFTH_FINGER_MIN{0};
constexpr byte FIFTH_FINGER_DELTA{( FIFTH_FINGER_MAX -  FIFTH_FINGER_MIN)* .1};


constexpr int FINGER_RECOGNITION_VALUE_DELTA{15};

constexpr int GESTURE_CHANGE_DELAY(2000);