#ifndef RAWUser
#define RAWUser

#include <vector>
#include "json.hpp"

struct RawUser
{
    // [ data ]
    std::string name;
    std::string avatar_url;
    std::string job_or_study;
    std::string hobbies;
    std::string localisation;
    std::string subscription_date;
    int message_count;
    int age;

    // [ methods ]
    using JSON = nlohmann::json;
    void read(const JSON& input);
    void write(JSON& output);
};

#endif /* end of include guard: RAWUser */
