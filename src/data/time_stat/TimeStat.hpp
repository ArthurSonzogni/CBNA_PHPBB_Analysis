#ifndef TIMESTAT_H
#define TIMESTAT_H

#include "data/raw/RawMessage.hpp"
#include <map>
#include <tuple>

class TimeStat
{
public: 
    void add_message(const RawMessage&);
    void print_summary(std::ostream&);
private:
    std::map<Date,int64_t> count;
    std::map<int,int64_t> count_year;
    std::map<std::pair<int,int>,int64_t> count_year_month;
    std::map<int,int64_t> count_month;
    void print_summary_year(std::ostream& out);
    void print_summary_month(std::ostream& out);
    void print_summary_year_month(std::ostream& out);
};

#endif /* end of include guard: TIMESTAT_H */
