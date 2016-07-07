#ifndef RAWTOPIC_H
#define RAWTOPIC_H

#include "RawMessage.hpp"
#include <vector>

struct RawTopic
{
    std::string title;
    std::vector<std::string> path;

    std::vector<RawMessage> messages;
};

#endif /* end of include guard: RAWTOPIC_H */
