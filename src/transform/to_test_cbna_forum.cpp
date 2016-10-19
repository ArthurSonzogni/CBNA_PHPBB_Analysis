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
    std::map<std::string,int> user_id_map;
    int next_user_id = 0;
    std::string user_directory = directory+"/message_board/contents/users/";
    mkdir(user_directory);

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
            //-------------
            // User
            //-------------
            int user_id;
            if (user_id_map.count(message.author))
            {
              user_id = user_id_map[message.author];
            }
            else
            {
              user_id = next_user_id;
              next_user_id++;
              user_id_map[message.author] = user_id;
              JSON json;
              json["avatar"] = "0.png";
              json["email"] = "unknown@lecbna.org";
              json["name"] = message.author;
              json["nickname"] = message.author;
              json["password"] = message.author;
              json["signupdate"] = "2016-01-01T00:00:00";
              std::ofstream file(user_directory + std::to_string(user_id));
              file << std::setw(4) << json;
            }

            JSON json;
            json["authors"].push_back(user_id);
            json["date"] = "2016-01-01T00:00:00";
            json["content"] = message.content;
            std::ofstream file(topic_directory + "/messages/"
                + std::to_string(message_id++));
            file << std::setw(4) << json;
        }
    }
}
