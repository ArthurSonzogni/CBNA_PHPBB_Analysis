#include "RawUser.hpp"

void RawUser::read(const JSON& input)
{
		hobbies           = input["hobbies"];
		subscription_date = input["subscription_date"];
    age               = input["age"];
    avatar_url        = input["avatar_url"];
    job_or_study      = input["job_or_study"];
    localisation      = input["localisation"];
    message_count     = input["message_count"];
    name              = input["name"];
    subscription_date = input["subscription_date"];
}

void RawUser::write(JSON& output)
{
		output["hobbies"]           = hobbies;
		output["subscription_date"] = subscription_date;
    output["age"]               = age;
    output["avatar_url"]        = avatar_url;
    output["job_or_study"]      = job_or_study;
    output["localisation"]      = localisation;
    output["message_count"]     = message_count;
    output["name"]              = name;
    output["subscription_date"] = subscription_date;
}
