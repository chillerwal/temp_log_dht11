#ifndef _TEMP_SDLOG_H_
#define _TEMP_SDLOG_H_

#include <SPI.h> // SD by Arduino
#include <SD.h> // SD by Arduino
#include "logtime.h"

namespace temp_log
{
    constexpr char _LOG_BOOT = 'b';
    constexpr char _LOG_TEMP = 't';
    constexpr char _LOG_HUMIDITY = 'h';

    bool init_sd_logging(const unsigned char& sd_pin);
    bool fileExists(const String& filename);
    bool deleteFile(const String& filename);
    bool appendToFile(const String& text, const String& filename);
    String readFile(const String& filename);

    void log_boot(const sdlog::LogTime& lt);
    void log_temperature(const sdlog::LogTime& lt, const float& current_temperature);
    void log_humidity(const sdlog::LogTime& lt, const float& current_humidity);
}

#endif