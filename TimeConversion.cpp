#include "TimeConversion.h"

namespace min_time
{
    String to_string(const TimeHM& origin)
    {
        String out{""};
		if(origin.is_valid())
		{
			unsigned char time[2]{ origin.get_hours(), origin.get_minutes() };
			out = String((time[0] % 100) / 10)
				+ String((time[0] % 10))
				+ String(_TIME_SEPARATOR)
				+ String((time[1] % 100) / 10)
				+ String((time[1] % 10));
		}
		else
		{
			out = "--" + String(_TIME_SEPARATOR) + "--";
		}

        return out;
    }

}