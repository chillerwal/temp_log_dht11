#include "temp_sdlog.h"

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
        String out = "";

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
        String out {""};
        
        // Generate Output for logging
        out += lt.iso_now(false, false);
        lt.append_separator(out);
        out += _LOG_BOOT;
        
        appendToFile(out, lt.current_filename());
    
        return;
    }

    void log_temperature(const sdlog::LogTime& lt, const float& current_temperature)
    {
        String out {""};
        
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
        String out {""};
        
        out += lt.iso_now(false, false);
        lt.append_separator(out);
        out += _LOG_HUMIDITY;
        lt.append_separator(out);
        out += (String) current_humidity;

        appendToFile(out, lt.current_filename());

        return;
    }

}