/*! @file temp_sdlog_dht11.cpp
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

#include "temp_sdlog_dht11.h"

namespace temp_log
{    
    bool init_sd_logging(const unsigned char& sd_pin){
        if(!SD.begin(sd_pin)){
            Serial.println(F("E: SD fail"));
            return false;
        }
        
        Serial.println(F("i: SD OK"));
        return true;
    }

    bool fileExists(const String& filename){
        return SD.exists(filename);
    }

    bool deleteFile(const String& filename){
        return SD.remove(filename);
    }

    bool appendToFile(const String& text, const String& filename){
        File currentfile = SD.open(filename, FILE_WRITE);
        
        if(!currentfile){
            Serial.println("E: " + filename + " no access");
            return false;
        }

        currentfile.println(text);
        currentfile.close();
        return true;
    }

    String readFile(const String& filename)
    {
        String out{ "" };

        // check if file exists
        if(!SD.exists(filename))
        {
            Serial.println("E: \"" + filename + "\" no exist");
            return "";
        }
        
        // open file
        File openfile = SD.open(filename);
        Serial.println("i: \"" + filename + "\" opened.");

        // read content and return into pointer
        out = openfile.read();
        
        // close file
        openfile.close();

        return out;
    }

    void log_boot(const sdlog::LogTime& lt)
    {
        String out { "" };
        
        // Generate Output for logging
        out += lt.iso_now(false, false);
        lt.append_separator(out);
        out += _LOG_BOOT;
        
        appendToFile(out, lt.current_filename());
    
        return;
    }

    void log_temperature(const sdlog::LogTime& lt, const float& current_temperature)
    {
        String out{ "" };
        
        out += lt.iso_now(false, false);
        lt.append_separator(out);
        out += _LOG_TEMP;
        lt.append_separator(out);
        out += (String) current_temperature;

        appendToFile(out, lt.current_filename());

        return;
    }

    void log_humidity(const sdlog::LogTime& lt, const float& current_humidity)
    {
        String out { "" };
        
        out += lt.iso_now(false, false);
        lt.append_separator(out);
        out += _LOG_HUMIDITY;
        lt.append_separator(out);
        out += (String) current_humidity;

        appendToFile(out, lt.current_filename());

        return;
    }

}