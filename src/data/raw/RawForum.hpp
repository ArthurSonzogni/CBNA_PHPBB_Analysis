#ifndef RAWFORUM_H
#define RAWFORUM_H

#include <map>
#include "RawTopic.hpp"

struct RawForum
{
    std::map<int,RawTopic> topics;
};

#endif /* end of include guard: RAWFORUM_H */
