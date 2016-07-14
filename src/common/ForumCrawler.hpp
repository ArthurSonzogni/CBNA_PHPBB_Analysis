#ifndef FORUMCRAWLER_HPP
#define FORUMCRAWLER_HPP

#include "data/raw/RawForum.hpp"

class ForumCrawler
{
public:
    ForumCrawler(const std::string& website);

    bool parse();
    void load(const std::string& directory);
    void save(const std::string& directory);
private:

    RawForum rawForum;
    std::string website;
    int getStartingPoint();
};

#endif /* end of include guard: FORUMCRAWLER_HPP */
