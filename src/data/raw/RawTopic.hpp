#ifndef RAWTOPIC_H
#define RAWTOPIC_H

#include "RawMessage.hpp"
#include <vector>
#include "json.hpp"

struct RawTopic
{
    // [ data ]
    std::string title;
    std::vector<std::string> path;
    std::vector<RawMessage> messages;

    // [ methods ]
    using JSON = nlohmann::json;
    void read(const JSON& input);
    void write(JSON& output);
};

#endif /* end of include guard: RAWTOPIC_H */
