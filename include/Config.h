#pragma once

constexpr byte FIRST_FINGER_PIN{A1};
constexpr uint16_t FIRST_FINGER_MAX{120};
constexpr uint16_t FIRST_FINGER_MIN{50};
constexpr uint16_t FIRST_FINGER_DELTA{static_cast<uint16_t>((FIRST_FINGER_MAX - FIRST_FINGER_MIN)* .2)};

constexpr byte SECOND_FINGER_PIN{A3};
constexpr uint16_t SECOND_FINGER_MAX{55};
constexpr uint16_t SECOND_FINGER_MIN{0};
constexpr uint16_t SECOND_FINGER_DELTA{static_cast<uint16_t>((SECOND_FINGER_MAX - SECOND_FINGER_MIN)* .2)};

constexpr byte THIRD_FINGER_PIN{A2};
constexpr uint16_t THIRD_FINGER_MAX{63};
constexpr uint16_t THIRD_FINGER_MIN{0};
constexpr uint16_t THIRD_FINGER_DELTA{static_cast<uint16_t>((THIRD_FINGER_MAX - THIRD_FINGER_MIN)* .2)};

constexpr byte FOURTH_FINGER_PIN{A0};
constexpr uint16_t FOURTH_FINGER_MAX{50};
constexpr uint16_t FOURTH_FINGER_MIN{0};
constexpr uint16_t FOURTH_FINGER_DELTA{static_cast<uint16_t>((FOURTH_FINGER_MAX - FOURTH_FINGER_MIN)* .2)};

constexpr byte FIFTH_FINGER_PIN{A8};
constexpr uint16_t FIFTH_FINGER_MAX{50};
constexpr uint16_t FIFTH_FINGER_MIN{0};
constexpr uint16_t FIFTH_FINGER_DELTA{static_cast<uint16_t>((FIFTH_FINGER_MAX - FIFTH_FINGER_MIN)* .2)};


constexpr byte BUTTON{4};
constexpr byte LED_1{5};
constexpr byte LED_2{6};

constexpr int FINGER_RECOGNITION_VALUE_DELTA{15};

constexpr int GESTURE_CHANGE_DELAY(1000);