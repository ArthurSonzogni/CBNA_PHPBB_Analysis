#include "download/HTTPDownloader.hpp"
#include <iostream>
#include <string>

#include "common/ForumCrawler.hpp"
#include "transform/to_word_usage.hpp"

#include <cstdlib> // system()

int main(int argc, char** argv)
{
    const std::string website = "cbna.forumactif.com";
    const std::string save_dir = "save";

    std::system(("mkdir -p " + save_dir).c_str());

    ForumCrawler forumCrawler(website, save_dir);
    forumCrawler.load();

    auto word_usage = to_word_usage(forumCrawler.raw_forum());
    word_usage.print_summary(std::cout);

    while(true)
    {
        forumCrawler.parse();
    }
    return EXIT_SUCCESS;
}
