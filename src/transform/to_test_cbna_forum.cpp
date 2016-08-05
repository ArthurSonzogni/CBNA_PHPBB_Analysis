#include "to_test_cbna_forum.hpp"
#include <fstream>

using JSON = nlohmann::json;


static bool mkdir(const std::string& directory)
{
    std::cout << ("mkdir -p " + directory) << std::endl;
    return std::system(("mkdir -p " + directory).c_str());
}

void to_test_cbna_forum(const RawForum& forum, const std::string& directory)
{
    std::map<std::string,int> category_id_map;

    //-------------
    // Topics
    //-------------
    for(auto& topic_pair : forum.topics)
    {
        auto& topic_id = topic_pair.first;
        auto& topic    = topic_pair.second;

        int& category_id = category_id_map[topic.path[2]];
        bool create_category = false;
        if (!category_id)
        {
            category_id = category_id_map.size();
            create_category = true;
        }

        std::string category_directory =
            directory + "/message_board/contents/categories/" +
            std::to_string(category_id);
        std::string topic_directory = category_directory +
             "/topics/" + std::to_string(topic_id);
        mkdir(topic_directory);

        //---------------------
        // Making new category
        //---------------------
        if (create_category)
        {
            JSON json;
            json["description"] = "";
            json["name"] = topic.path[2];
            std::ofstream(category_directory+"/info") << std::setw(4) << json;
        }

        //-------------
        // Topic info
        //-------------
        std::ofstream file(topic_directory + "/info");
        JSON json;
        json["creation_date"] = "2016-01-01T00:00:00";
        json["draft"] = false;
        json["locked"] = false;
        json["title"] = topic.title;
        file << std::setw(4) << json;

        //-------------
        // Messages
        //-------------
        mkdir(topic_directory+"/messages/");
        int message_id = 0;
        for(auto& message : topic.messages)
        {
            JSON json;
            json["authors"].push_back(0);
            json["date"] = "2016-01-01T00:00:00";
            //json["date"] = message.date.to_string();
            json["text"] = message.content;
            std::ofstream file(topic_directory +
                "/messages/" + std::to_string(message_id++));
            file << std::setw(4) << json;
        }
    }
}
