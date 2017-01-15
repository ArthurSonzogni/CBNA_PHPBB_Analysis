#include <fstream>
#include "to_avatar_list.hpp"

void to_avatar_list_bbcode(const RawForum& forum, const std::string& directory)
{
  std::ofstream file(directory + "/avatar.txt");
  for(auto& user : forum.users) 
  {
    std::string url = user.second.avatar_url;
    if (url.size()>4 && url.substr(0,4) == "http")
      file << "[img]" << url << "[/img]" << std::endl;
  }
}
