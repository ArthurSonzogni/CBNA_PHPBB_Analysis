#ifndef RAWMESSAGE_H
#define RAWMESSAGE_H

#include <string>
#include "json.hpp"


struct RawMessage
{
    // [ data ]
    std::string author;
    std::string content;

    // [ methods ]
    using JSON = nlohmann::json;
    void read(const JSON& input);
    void write(JSON& output);
};

#endif /* end of include guard: RAWMESSAGE_H */
