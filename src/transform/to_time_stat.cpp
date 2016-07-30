#include "to_time_stat.hpp"


TimeStat to_time_stat(const RawForum& forum)
{
    TimeStat result;
    for(auto& topic_entry  : forum.topics)
    {
        std::cout << "Computing time stat, topic = "
                  << topic_entry.first << '\r' << std::flush;
        auto& topic = topic_entry.second;
        for(auto& message : topic.messages)
        {
            result.add_message(message);
        }
    }
    return result;
}
