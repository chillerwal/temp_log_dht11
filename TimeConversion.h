#ifndef _TIME_CONVERSION_H_
#define _TIME_CONVERSION_H_

#include <Arduino.h>
#include "TimeHM.h"

namespace min_time
{
    constexpr char _TIME_SEPARATOR = ':';
    constexpr char _DURATION_SEPARATOR = '!';

    String to_string(const TimeHM& origin);
}


#endif