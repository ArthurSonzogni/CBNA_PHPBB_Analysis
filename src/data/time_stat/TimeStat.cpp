#include "TimeStat.hpp"


void TimeStat::add_message(const RawMessage& message)
{
    count[message.date]++;
    count_year[message.date.year]++;
    count_month[message.date.month]++;
    std::pair<int,int> pair(message.date.year,message.date.month);
    count_year_month[pair]++;
}

void TimeStat::print_summary(std::ostream& out)
{
    print_summary_year(out);
    print_summary_month(out);
    print_summary_year_month(out);
}

void TimeStat::print_summary_year(std::ostream& out)
{
    int64_t sum = 0;
    for(auto& it : count_year)
      sum+=it.second;
    out << std::endl;
    out << " +------+----------+----------+" << std::endl;
    out << " | YEAR |    COUNT |    RATIO |" << std::endl;
    out << " +------+----------+----------+" << std::endl;
    for(auto& it : count_year)
    {
      double ratio = double(it.second)/double(sum);
      out
        << " | " << std::setw(4) << it.first 
        << " | " << std::setw(8) << it.second
        << " | " << std::setw(7) << int(10000*ratio)*0.01 << "%"
        << " | " << std::endl;
    }
    out << " +------+----------+----------+" << std::endl;
}

void TimeStat::print_summary_month(std::ostream& out)
{
    int64_t sum = 0;
    for(auto& it : count_month)
      sum+=it.second;
    out << std::endl;
    out << " +-------+----------+----------+" << std::endl;
    out << " | MONTH |    COUNT |    RATIO |" << std::endl;
    out << " +-------+----------+----------+" << std::endl;
    for(auto& it : count_month)
    {
      double ratio = double(it.second)/double(sum);
      out
        << " | " << std::setw(5) << it.first 
        << " | " << std::setw(8) << it.second
        << " | " << std::setw(7) << int(10000*ratio)*0.01 << "%"
        << " | " << std::endl;
    }
    out << " +-------+----------+----------+" << std::endl;
}

void TimeStat::print_summary_year_month(std::ostream& out)
{
    int64_t sum = 0;
    for(auto& it : count_year_month)
      sum+=it.second;
    out << std::endl;
    out << " +------+-------+----------+----------+" << std::endl;
    out << " | YEAR | MONTH |    COUNT |    RATIO |" << std::endl;
    out << " +------+-------+----------+----------+" << std::endl;
    for(auto& it : count_year_month)
    {
      double ratio = double(it.second)/double(sum);
      out
        << " | " << std::setw(4) << it.first.first
        << " | " << std::setw(5) << it.first.second
        << " | " << std::setw(8) << it.second
        << " | " << std::setw(7) << int(10000*ratio)*0.01 << "%"
        << " | " << std::endl;
    }
    out << " +------+-------+----------+----------+" << std::endl;
}
