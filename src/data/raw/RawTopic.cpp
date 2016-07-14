#include "RawTopic.hpp"

void RawTopic::read(const JSON& input)
{
    title = input["title"];

    path.clear();
    for(auto& p : input["path"])
    {
        path.push_back(p);
    }

    messages.clear();
    for(auto& message : input["messages"])
    {
        RawMessage m;
        m.read(message);
        messages.push_back(m);
    }

    id = input["id"];
}

void RawTopic::write(JSON& output)
{
    output["title"] = title;

    for(auto& p : path)
    {
        output["path"].push_back(p);  
    }

    for(auto& message : messages)
    {
        JSON json;
        message.write(json);
        output["messages"].push_back(json);
    }

    output["id"] = id;
}
