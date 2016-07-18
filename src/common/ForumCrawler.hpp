#ifndef FORUMCRAWLER_HPP
#define FORUMCRAWLER_HPP

#include "data/raw/RawForum.hpp"

class ForumCrawler
{
public:
    ForumCrawler(const std::string& website,
                 const std::string& save_dir);

    bool parse();
    void load();

    const RawForum& raw_forum();
private:

    void save();
    void save(int topic_id);

    RawForum rawForum;

    std::string website;
    std::string save_dir;
    int starting_point = 1;
};

#endif /* end of include guard: FORUMCRAWLER_HPP */
