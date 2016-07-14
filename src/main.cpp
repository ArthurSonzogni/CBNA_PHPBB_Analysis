#include "download/HTTPDownloader.hpp"
#include <iostream>
#include <string>

#include "common/ForumCrawler.hpp"

#include <cstdlib> // system()

int main(int argc, char** argv)
{
    const std::string data_dir = "save";
    std::system(("mkdir -p " + data_dir).c_str());
    ForumCrawler forumCrawler("cbna.forumactif.com");
    while(true)
    {
      forumCrawler.load(data_dir);
      forumCrawler.parse();
      forumCrawler.save(data_dir);
    }
    return EXIT_SUCCESS;
}
