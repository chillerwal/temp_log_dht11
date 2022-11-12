/*
 * TimeMH.h by Tobias Rolke
 * Version: 2022-06-21/22-10
 *
 * Only stores hours and minutes in a small memory footprint.
 * Can add and substract times with or without rolling over midnight.
 * There is also a flag for detected invalid times, when overflow is
 * not active.
 * 
 * Made for use with Arduino, no dependencies.
 */


#ifndef _TIMEHM_H_
#define _TIMEHM_H_

namespace min_time
{
    constexpr unsigned char _FLAG_TIME_INVALID{ 0b10000000 };

    class TimeHM
    {
        protected:
        bool overflow;
        unsigned char hour;
        unsigned char minute;

        public:
        TimeHM();
        TimeHM(const unsigned char& h, const unsigned char& m);
        ~TimeHM() = default;

        char get_hours() const;
        char get_minutes() const;
        void set_hours(const unsigned char& h);
        void set_minutes(const unsigned char& m);
        void set_overflow(const bool& o);
        void add(const TimeHM& diff);
        void substract(const TimeHM& diff);
        bool equals(const TimeHM& comp) const;
        bool is_valid() const;
        void set_invalid();
        TimeHM operator+(const TimeHM& other) const;
        TimeHM operator-(const TimeHM& other) const;
        bool operator==(const TimeHM& other) const;
        bool operator<(const TimeHM& other) const;
    };
}

#endif