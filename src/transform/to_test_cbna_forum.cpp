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
    //-------------
    // Topics
    //-------------
    for(auto& topic_pair : forum.topics)
    {
        auto& topic_id = topic_pair.first;
        auto& topic    = topic_pair.second;

        std::string topic_directory =
            directory + "/message_board/contents" +
             "/topics/" + std::to_string(topic_id);
        mkdir(topic_directory);

        //-------------
        // Topic info
        //-------------
        std::ofstream file(topic_directory + "/info");
        JSON json;
        json["creation_date"] = "2016-01-01T00:00:00";
        json["draft"] = false;
        json["locked"] = false;
        // Quickfix, remove the first two char (0x22C2)
        // TODO(arthursonzogni): remove this once the bug is fixed.
        json["title"] = topic.title.substr(2,topic.title.size()-2);
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
            json["content"] = message.content;
            std::ofstream file(topic_directory +
                "/messages/" + std::to_string(message_id++));
            file << std::setw(4) << json;
        }
    }
}