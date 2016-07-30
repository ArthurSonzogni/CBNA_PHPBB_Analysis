#include "download/HTTPDownloader.hpp"
#include <iostream>
#include <string>

#include "common/ForumCrawler.hpp"
#include "transform/to_word_usage.hpp"
#include "transform/to_time_stat.hpp"

#include <cstdlib> // system()

int main(int argc, char** argv)
{
    const std::string website = "cbna.forumactif.com";
    const std::string save_dir = "save";

    if (std::system(("mkdir -p " + save_dir).c_str()) != EXIT_SUCCESS)
      return EXIT_FAILURE;

    ForumCrawler forumCrawler(website, save_dir);
    forumCrawler.load();

    auto time_stat = to_time_stat(forumCrawler.raw_forum());
    time_stat.print_summary(std::cout);

    auto word_usage = to_word_usage(forumCrawler.raw_forum());
    word_usage.print_summary(std::cout);

    while(true)
    {
        forumCrawler.parse();
    }
    return EXIT_SUCCESS;
}
