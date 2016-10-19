#include "ForumCrawler.hpp"
#include "parse/TopicParser.hpp"
#include "list_files.hpp"
#include <iostream>

#include <fstream>

using JSON = nlohmann::json;

ForumCrawler::ForumCrawler(const std::string& website,
                           const std::string& save_dir)
  : website(website),
    save_dir(save_dir)
{
}


bool ForumCrawler::parse()
{
    bool found_something = false;
    TopicParser topicParser(website);

    int fail_allowed_max = 200;
    int fail_allowed = fail_allowed_max;
    int remaining_topic_download = 10;
    for(int topic_id = starting_point; remaining_topic_download >=0; ++topic_id)
    {
        starting_point = topic_id+1;
        if (topicParser.parse(topic_id))
        {
            found_something = true;
            rawForum.topics[topic_id] = topicParser.toRaw();
            save(topic_id);
            fail_allowed = fail_allowed_max;
            remaining_topic_download--;
            save(topic_id);
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

void ForumCrawler::save()
{
    for(auto& topic_entry : rawForum.topics)
    {
        save(topic_entry.first);
    }
}

void ForumCrawler::save(int topic_id)
{
    auto& topic = rawForum.topics[topic_id];
    std::cout << "Saving topic n°"<< topic_id << '\r' << std::flush;
    JSON json;
    topic.write(json);
    std::ofstream file(save_dir + "/" + std::to_string(topic_id));
    file << std::setw(4) << json;
}

void ForumCrawler::load()
{
    for(auto& file_name : list_files(save_dir)) try
    {
      int id = std::stoi(file_name);
      std::cout << "Loading topic n°"<< id << '\r' << std::flush;
      JSON json;
      std::ifstream file(save_dir+"/"+file_name);
      file >> json;
      rawForum.topics[id].read(json);
      starting_point = std::max(starting_point,id+1);
    }
    catch(...){} // we catch exception from std::stoi
}

const RawForum& ForumCrawler::raw_forum()
{
    return rawForum;
}
