#include "Date.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>


// Members
// -------------
// uint8_t hour;
// uint8_t minute;
// uint8_t week;
// uint8_t day;
// uint8_t month;
// uint16_t year;


const std::vector<std::string> week_string = 
{
  "Lun",
  "Mar",
  "Mer",
  "Jeu",
  "Ven",
  "Sam",
  "Dim"
};

const std::vector<std::string> month_string = 
{
  "Jan",
  "Fév",
  "Mar",
  "Avr",
  "Mai",
  "Juin",
  "Juil",
  "Aoû",
  "Sep",
  "Oct",
  "Nov",
  "Déc"
};

void Date::fromString(const std::string& input) 
{
    data = input;
    // week
    for(int i = 0; i<week_string.size(); ++i)
    {
        if (input.find(week_string[i]) != std::string::npos)
            week = i;
    }
    // month
    for(int i = 0; i<month_string.size(); ++i)
    {
        if (input.find(month_string[i]) != std::string::npos)
            month = i;
    }

    std::stringstream ss(input);
    std::string tmp;
    if(!(std::getline(ss, tmp,' ')))      return ;
    if(!(std::getline(ss, tmp,' ')))      return ;
    if(!(std::stringstream(tmp)>>day))    return ;
    if(!(std::getline(ss, tmp,' ')))      return ;
    if(!(std::getline(ss, tmp,' ')))      return ;
    if(!(std::stringstream(tmp)>>year))   return ;
    if(!(std::getline(ss, tmp,' ')))      return ;
    if(!(std::getline(ss, tmp,':')))      return ;
    if(!(std::stringstream(tmp)>>hour))   return ;
    if(!(std::getline(ss, tmp,' ')))      return ;
    if(!(std::stringstream(tmp)>>minute)) return ;
}
const std::string& Date::to_string() const
{
    return data;
}
bool Date::operator<(const Date& other) const
{
    if (year<other.year)     return true;
    if (year>other.year)     return false;

    if (month<other.month)   return true;
    if (month>other.month)   return false;

    if (day<other.day)       return true;
    if (day>other.day)       return false;

    if (hour<other.hour)     return true;
    if (hour>other.hour)     return false;

    if (minute<other.minute) return true;
    if (minute>other.minute) return false;

    return false;
}

std::string Date::toString() const {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(4) << year << "-";
  ss << std::setfill('0') << std::setw(2) << month << "-";
  ss << std::setfill('0') << std::setw(2) << day;
  ss << "T";
  ss << std::setfill('0') << std::setw(2) << hour << ":";
  ss << std::setfill('0') << std::setw(2) << minute << ":";
  ss << std::setfill('0') << std::setw(2) << 0;
  return ss.str();
}
