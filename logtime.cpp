#include "logtime.h"

namespace sdlog
{
  LogTime::LogTime(){
      RTC_DS1307();
      this->prefix = ' ';
      return;
  }

  LogTime::~LogTime(){
      return;
  }

  String LogTime::iso_now(bool filesys, bool brackets) const
  {
    DateTime currentTime {now()};
    String out {""};
    char timeseparator {':'};

    if(filesys)
      timeseparator = '-';

    if(brackets)
      out += ("[");

    out += zerofill(currentTime.year(), 4);
    out += "-";
    out += zerofill(currentTime.month(), 2);
    out += "-";
    out += zerofill(currentTime.day(), 2);
    out += " ";
    out += zerofill(currentTime.hour(), 2);
    out += timeseparator;
    out += zerofill(currentTime.minute(), 2);
    out += timeseparator;
    out += zerofill(currentTime.second(), 2);
    
    if(brackets)
      out += "[";

    return out;
  }

  String LogTime::current_filename() const
  {
    DateTime currentTime {now()};
    String out{};

    if(this->prefix != ' ')
      out += prefix;

    out += zerofill(currentTime.year(), 4) + "-" + zerofill(currentTime.month(), 2);
    out += ".csv";

    return out;
  }

  String LogTime::year_month() const{
    DateTime currentTime = now();
    String out = "";

    out += zerofill(currentTime.year(), 4);
    out += "-";
    out += zerofill(currentTime.month(), 2);

    return out;
  }

  String LogTime::year() const
  {
    DateTime currentTime = now();
    String out = "";

    out = zerofill(currentTime.year(), 4);

    return out;
  }

  String LogTime::zerofill(int value, int numZero) const
  {
    String textOut = "";
    int multi = 1;
    
    for(int i = 0; i < (numZero-1); i++)
    {
      multi *= 10;
    }
    
    while(multi > value)
    {
      textOut.concat("0");
      if(multi > 10)
        multi /= 10;
      else
        break;
    }
    textOut.concat(value);
    return textOut;
  }

  void LogTime::set_prefix(char prefix)
  {
    this->prefix = prefix;
    return;
  }

  void LogTime::append_separator(String& text) const
  {
    text.concat(';');
    return;
  }
}