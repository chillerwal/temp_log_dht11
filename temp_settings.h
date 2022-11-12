#ifndef _TEMP_SETTINGS_H_
#define _TEMP_SETTINGS_H_

#include "Arduino.h"

namespace temp_log
{
    constexpr bool _SERIAL_LOGGING{true};
    constexpr bool _SD_LOGGING{true};

    constexpr float _OFFSET_TEMPERATURE{-0.0};
    constexpr float _OFFSET_HUMIDITY{-12.0};

    namespace pin
    {
        constexpr uint8_t _TEMP_SENSOR{5};
        constexpr unsigned char _LED_ONBOARD{13};
        constexpr unsigned char _SD{10};
    }
}

#endif