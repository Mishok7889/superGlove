#include "Utility.h"
#include "avr/wdt.h"
#include "Arduino.h"

void my_delay(uint16_t delay_in_miliseconds)
{
    wdt_reset();
    delay(delay_in_miliseconds);
}