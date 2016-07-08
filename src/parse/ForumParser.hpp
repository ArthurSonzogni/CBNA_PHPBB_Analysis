#ifndef FORUMPARSER_H
#define FORUMPARSER_H

#include "data/raw/RawForum.hpp"

class ForumParser
{
public:
    ForumParser(const std::string& website);
    bool parse();
    // TODO(arthursonzogni) : copy the whole structure ?
    RawForum toRaw(); 
private:

    RawForum rawForum;
    std::string website;
};

#endif /* end of include guard: FORUMPARSER_H */
