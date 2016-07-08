#include "RawMessage.hpp"

void RawMessage::read(const JSON& input)
{
    author = input["author"];
    content = input["content"];
}

void RawMessage::write(JSON& output)
{
    output["author"] = author;
    output["content"] = content;
}
