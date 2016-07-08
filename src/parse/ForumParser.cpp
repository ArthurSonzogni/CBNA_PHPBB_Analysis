#include "ForumParser.hpp"
#include "TopicParser.hpp"

#include <fstream>

using JSON = nlohmann::json;

ForumParser::ForumParser(const std::string& website):
    website(website)
{
}

bool ForumParser::parse()
{
    bool found_something = false;
    TopicParser topicParser(website);

    int fail_allowed_max = 10;
    int fail_allowed = fail_allowed_max;
    for(int topic_id = 13000; /*break below*/; ++topic_id)
    {
        if (topicParser.parse(topic_id))
        {
            found_something = true;
            rawForum.topics.push_back(topicParser.toRaw());
            fail_allowed = fail_allowed_max;

            // write topic
            JSON json;
            topicParser.toRaw().write(json);
            std::ofstream file("output_" + std::to_string(topic_id));
            file << std::setw(4) << json;
        }
        else
        {
            fail_allowed--;
            if (fail_allowed <= 0)
              break;
        }
    }
    return found_something;
}

RawForum ForumParser::toRaw()
{
    return rawForum;
}
