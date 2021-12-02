#pragma once
#include "algorithm"

template<typename T, typename U>
struct Tuple
{
    T first;
    U second;
};

//To avoid using objects there will be one big array which would be using partly
template<typename T>
class MedianFilter
{
public:
    MedianFilter(int lengthIn);
    void push(const T& val);
    T median();
private:
    static constexpr int MAX_LEN{20};
    int currIdx;
    const int length;
    T values[MAX_LEN];
};

template<typename T>
MedianFilter<T>::MedianFilter(int lengthIn) : currIdx{}, length{lengthIn} {}

template<typename T>
void MedianFilter<T>::push(const T& val)
{
    values[currIdx] = val;
    ++currIdx;
    currIdx = currIdx >= length ? 0 : currIdx;
}

template<typename T>
T MedianFilter<T>::median()
{
    std::sort(values, values + length);
    if(length % 2 == 0)
    {
        return (values[length/2 - 1] + values[length/2]) / 2;
    }
    else
    {
        return values[length/2];
    }
}