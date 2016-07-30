#include "RawMessage.hpp"

void RawMessage::read(const JSON& input)
{
    author = input["author"];
    content = input["content"];
    date.fromString(input["date"]);
}

void RawMessage::write(JSON& output)
{
    output["author"] = author;
    output["content"] = content;
    output["date"] = date.to_string();
}
