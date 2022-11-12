#ifndef _LOGTIME_H_
#define _LOGTIME_H_

#include <RTClib.h> // RTCLib by Adafruit

namespace sdlog
{
    class LogTime : public RTC_DS1307{
        public:
            LogTime();
            ~LogTime();
            String iso_now(bool filesys = false, bool brackets = false) const;
            String current_filename() const;
            String year_month() const;
            String year() const;
            String zerofill(int value, int numZero = 1) const;
            void set_prefix(char prefix);
            void append_separator(String& text) const;
        private:
            char prefix;
    };

}

#endif