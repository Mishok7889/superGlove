#include "Utility.h"
#include "States.h"
#include "Config.h"

FingersPosition readFingersPosition()
{
    FingersPosition res{};
    res[0] = analogRead(FIRST_FINGER_PIN);
    res[1] = analogRead(SECOND_FINGER_PIN);
    res[2] = analogRead(THIRD_FINGER_PIN);
    res[3] = analogRead(FOURTH_FINGER_PIN);
    res[4] = analogRead(FIFTH_FINGER_PIN);
    return res;
}



SimpleGesture recordSimpleGesture(const int numberOfActions, int numberOfMeasures)
{
    SimpleGesture res{};

    Serial.println("---Starting recognition---\n");
    delay(2000);
    //Delay to prepare for recognition

    for(int i{}; i < numberOfActions; ++i)
    {
        Serial.println("Hold your hand still");
        delay(1000);

        res.add(readMedianValue(numberOfMeasures));
    }
    
    return res;
}

void debugPrint()
{
    Serial.println(String(analogRead(FIRST_FINGER_PIN))  + ", "+
                   String(analogRead(SECOND_FINGER_PIN)) + ", " +
                   String(analogRead(THIRD_FINGER_PIN))  + ", "+
                   String(analogRead(FOURTH_FINGER_PIN)) + ", " +
                   String(analogRead(FIFTH_FINGER_PIN))+ ", ");
}

void printPositions(const FingersPosition& fingers)
{
    Serial.print(fingers[0] + String(',') + 
                 fingers[1] + String(',') +
                 fingers[2] + String(',') +
                 fingers[3] + String(',') +
                 fingers[4]);
}
void printGesture(const SimpleGesture& gesture)
{
    for(int i{}; i < gesture.size(); ++i)
    {
        printPositions(gesture[i]);
        Serial.println();
    }
    Serial.println();
}

FingersPosition readMedianValue(const int numberOfMeasures, const int readingDelay)
{
    static MedianFilter<uint16_t> filter[5]{
                                        MedianFilter<uint16_t>(numberOfMeasures),
                                        MedianFilter<uint16_t>(numberOfMeasures),
                                        MedianFilter<uint16_t>(numberOfMeasures),
                                        MedianFilter<uint16_t>(numberOfMeasures),
                                        MedianFilter<uint16_t>(numberOfMeasures)};

    for(int j{numberOfMeasures}; j > 0; --j)
    {
        Serial.println("+++Recognizing " + String(j) + String("+++"));
        delay(500);
        FingersPosition pos{readFingersPosition()};
        for (int k{}; k < 5; ++k)
        {
            filter[k].push(pos[k]);
        }
    }

    FingersPosition res;
    for (int k{}; k < 5; ++k)
    {
        res[k] = filter[k].median();
    }
    return res;
}