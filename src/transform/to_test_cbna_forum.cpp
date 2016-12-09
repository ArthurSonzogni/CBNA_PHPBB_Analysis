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
    std::string user_directory = directory+"/message_board/users/";
    std::string topic_directory = directory+"/message_board/contents/topics/";
    mkdir(user_directory);
    mkdir(topic_directory);

    //-------------
    // Topics
    //-------------
    for(auto& topic_pair : forum.topics)
    {
        auto& topic_id = topic_pair.first;
        auto& topic    = topic_pair.second;

        std::string topic_filename = topic_directory + std::to_string(topic_id);

        //-------------
        // Topic info
        //-------------
        std::ofstream file(topic_filename);
        JSON topic_json;
        topic_json["creation_date"] = "2016-01-01T00:00:00";
        topic_json["draft"] = false;
        topic_json["locked"] = false;
        // Quickfix, remove the first two char (0x22C2)
        // TODO(arthursonzogni): remove this once the bug is fixed.
        topic_json["title"] = topic.title.substr(2,topic.title.size()-2);
        topic_json["messages"] = JSON::array();

        //-------------
        // Messages
        //-------------
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
              JSON user_json;
              user_json["avatar"] = "0.png";
              user_json["email"] = "unknown@lecbna.org";
              user_json["name"] = message.author;
              user_json["nickname"] = message.author;
              user_json["password"] = message.author;
              user_json["is_moderator"] = false;
              user_json["is_admin"] = false;
              user_json["signupdate"] = "2016-01-01T00:00:00";
              std::ofstream file(user_directory + std::to_string(user_id));
              file << std::setw(2) << user_json;
            }

            JSON message_json;
            message_json["authors"].push_back(user_id);
            message_json["date"] = "2016-01-01T00:00:00";
            message_json["content"] = message.content;
            topic_json["messages"].push_back(message_json);
        }
        file << std::setw(2) << topic_json;
    }
}
