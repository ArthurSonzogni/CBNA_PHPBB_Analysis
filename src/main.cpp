#include "download/HTTPDownloader.hpp"
#include <iostream>
#include <string>
#include <fstream>

#include "common/ForumCrawler.hpp"
#include "transform/to_word_usage.hpp"
#include "transform/to_time_stat.hpp"
#include "transform/to_test_cbna_forum.hpp"
#include "transform/to_avatar_list.hpp"

#include <cstdlib> // system()

std::ofstream
  file_user_best_word("stat_user_best_word.txt"),
  file_word_best_user("stat_word_best_user.txt"),
  file_section("stat_section.txt"),
  file_word_to_view("stat_word_to_view.txt");

int main(int argc, char** argv)
{
    const std::string website = "cbna.forumactif.com";
    const std::string save_dir = "save";

    if (std::system(("mkdir -p " + save_dir + "/users").c_str()) != EXIT_SUCCESS)
      return EXIT_FAILURE;
    if (std::system(("mkdir -p " + save_dir + "/topics").c_str()) != EXIT_SUCCESS)
      return EXIT_FAILURE;

    ForumCrawler forumCrawler(website, save_dir);
    forumCrawler.load();
    forumCrawler.parse();

    //auto time_stat = to_time_stat(forumCrawler.raw_forum());
    //time_stat.print_summary(std::cout);

    //auto word_usage = to_word_usage(forumCrawler.raw_forum(),
        //{"C++","Java","Javascript","Python","Haxe","Ruby","C#","oui","non"});
    ////word_usage.print_summary(std::cout);
    //word_usage.print_user_best_word(file_user_best_word);
    //word_usage.print_word_best_user(file_word_best_user);
    //word_usage.print_section(file_section);
    //word_usage.print_word_to_view(file_word_to_view);


    // export the forum to test.cbna
    to_test_cbna_forum(forumCrawler.raw_forum(),"cbna_forum");
    //to_avatar_list_bbcode(forumCrawler.raw_forum(), "avatar");
    return EXIT_SUCCESS;
}
