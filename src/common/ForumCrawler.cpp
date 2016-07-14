#include "ForumCrawler.hpp"
#include "parse/TopicParser.hpp"
#include "list_files.hpp"
#include <iostream>

#include <fstream>

using JSON = nlohmann::json;

ForumCrawler::ForumCrawler(const std::string& website)
  : website(website)
{
}


bool ForumCrawler::parse()
{
    bool found_something = false;
    TopicParser topicParser(website);

    int fail_allowed_max = 10;
    int fail_allowed = fail_allowed_max;
    int remaining_topic_download = 10;
    for(int topic_id = getStartingPoint(); remaining_topic_download >=0; ++topic_id)
    {
        if (topicParser.parse(topic_id))
        {
            found_something = true;
            rawForum.topics[topic_id] = topicParser.toRaw();
            fail_allowed = fail_allowed_max;
            remaining_topic_download--;
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

void ForumCrawler::save(const std::string& directory)
{
    for(auto& topic_entry : rawForum.topics)
    {
        auto& id    = topic_entry.first;
        auto& topic = topic_entry.second;
        std::cout << "Saving topic n°"<< id << std::endl;
        JSON json;
        topic.write(json);
        std::ofstream file(std::to_string(id));
        file << std::setw(4) << json;
    }
}

void ForumCrawler::load(const std::string& directory)
{
    for(auto& file_name : list_files(directory)) try
    {
      int id = std::stoi(file_name);
      std::cout << "Loading topic n°"<< id << std::endl;
      JSON json;
      std::ifstream file(directory+"/"+file_name);
      file >> json;
      rawForum.topics[id].read(json);
    }
    catch(...){} // we catch exception from std::stoi
}

int ForumCrawler::getStartingPoint()
{
    if (rawForum.topics.empty())
      return 0;
    else
      return rawForum.topics.rbegin()->first + 1;
}
