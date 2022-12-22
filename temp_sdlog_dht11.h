/*! @file temp_sdlog_dht11.h
 *! @author Tobias Rolke (github.com/randomguyfromtheinternet/)
 *! @version 1.0
 *! @date 2022-12-22
 *! @brief SD Logging helper functions for DHT11 sensor
 *! @copyright GPLv3
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _TEMP_SDLOG_DHT11_H_
#define _TEMP_SDLOG_DHT11_H_

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