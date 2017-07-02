#include "ForumCrawler.hpp"
#include "parse/TopicParser.hpp"
#include "parse/UserParser.hpp"
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
  return
    parse_topics() &&
    parse_users() &&
    true;
}

bool ForumCrawler::parse_topics()
{
    bool found_something = false;
    TopicParser topic_parser(website);

    int fail_allowed_max = 500;
    int fail_allowed = fail_allowed_max;
    for(int topic_id = topic_next; ; ++topic_id)
    {
        topic_next = topic_id;
        if (topic_parser.parse(topic_id))
        {
            found_something = true;
            rawForum.topics[topic_id] = topic_parser.toRaw();
            save_topic(topic_id);
            fail_allowed = fail_allowed_max;
        }
        else
        {
            std::cout << "Fail topic = " << topic_id << "" << std::endl;
            fail_allowed--;
            if (fail_allowed <= 0)
              break;
        }
    }
    return found_something;
}

bool ForumCrawler::parse_users()
{
    bool found_something = false;
    UserParser user_parser(website);

    int fail_allowed_max = 500;
    int fail_allowed = fail_allowed_max;
    for(int user_id = user_next; ; ++user_id)
    {
        user_next = user_id+1;
        if (user_parser.parse(user_id))
        {
            found_something = true;
            rawForum.users[user_id] = user_parser.toRaw();
            save_user(user_id);
            fail_allowed = fail_allowed_max;
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
		// save users
    for(auto& user_entry : rawForum.users)
        save_user(user_entry.first);

		// save topics
    for(auto& topic_entry : rawForum.topics)
        save_topic(topic_entry.first);
}

void ForumCrawler::save_topic(int topic_id)
{
    auto& topic = rawForum.topics[topic_id];
    std::cout << "Saving topic n°"<< topic_id << '\r' << std::flush;
    JSON json;
    topic.write(json);
    std::ofstream file(save_dir + "/topics/" + std::to_string(topic_id));
    file << std::setw(4) << json;
}

void ForumCrawler::save_user(int user_id)
{
    auto& user = rawForum.users[user_id];
    std::cout << "Saving user n°"<< user_id << '\r' << std::flush;
    JSON json;
    user.write(json);
    std::ofstream file(save_dir + "/users/" + std::to_string(user_id));
    file << std::setw(4) << json;
}

void ForumCrawler::load()
{
		load_topics();
		load_users();
}

void ForumCrawler::load_topics()
{
    for(auto& file_name : list_files(save_dir + "/topics")) try
    {
      int id = std::stoi(file_name);
      std::cout << "Loading topic n°"<< id << std::endl;
      JSON json;
      std::ifstream file(save_dir+"/topics/"+file_name);
      file >> json;
      rawForum.topics[id].read(json);
      topic_next = std::max(topic_next,id+1);
    }
    catch(...){
      std::cerr << "Fail to load " << file_name << std::endl;
    } // we catch exception from std::stoi
}

void ForumCrawler::load_users()
{
    for(auto& file_name : list_files(save_dir + "/users")) try
    {
      int id = std::stoi(file_name);
      std::cout << "Loading user n°"<< id << std::endl;
      JSON json;
      std::ifstream file(save_dir+"/users/"+file_name);
      file >> json;
      rawForum.users[id].read(json);
      user_next = std::max(user_next,id+1);
    }
    catch(...){} // we catch exception from std::stoi
}

const RawForum& ForumCrawler::raw_forum()
{
    return rawForum;
}
