#ifndef DATE_H
#define DATE_H

#include <cstdint>
#include <string>

// A simple data structure to parse data
// with the following format : 
// Mer 19 Déc 2007 - 17:35
struct Date
{
    std::string data;
    int hour   = 0;
    int minute = 0;
    int week   = 0;
    int day    = 0;
    int month  = 0;
    int year   = 0;

    void fromString(const std::string&);
    const std::string& to_string() const;
    bool operator<(const Date& other) const;
    std::string toString() const;
};

#endif /* end of include guard: DATE_H */
