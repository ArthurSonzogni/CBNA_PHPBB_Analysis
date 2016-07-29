#include "to_word_usage.hpp"
#include <iostream>

static bool is_good_char(const char c)
{
  return (c>='a' && c<='z')
      || (c>='A' && c<='Z')
      || (c>='0' && c<='9');
}

std::vector<std::string> split(const std::string& text)
{
    std::vector<std::string> result;
    int left = 0;
    int right = 0;
    auto eat = [&]()
    {
        result.push_back(text.substr(left,right-left));
    };
    auto place_left = [&]()
    {
        left = right;
        while(left < text.size() && !is_good_char(text[left]))
          ++left;
        right = left;
    };
    auto place_right = [&]()
    {
        while(right < text.size() && is_good_char(text[right]))
          ++right;
    };
    while(1)
    {
      place_left();
      if (left >= text.size()) break;
      place_right();
      eat();
    }

    return result;
}

WordUsage to_word_usage(const RawForum& forum)
{
    WordUsage usage;
    for(auto& topic_entry  : forum.topics)
    {
        std::cout << "Computing word usage, topic = "
                  << topic_entry.first << '\r' << std::flush;
        auto& topic = topic_entry.second;
        std::string section = topic.path.size() >= 3
                            ? topic.path.at(2)
                            : std::string();
        for(auto& message : topic.messages)
        {
            std::string user = message.author;
            for(auto& word : split(message.content))
            {
                usage.add(word,user,section);
            }
        }
    }
    return usage;
};

