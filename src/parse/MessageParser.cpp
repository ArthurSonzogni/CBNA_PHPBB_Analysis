#include "MessageParser.hpp"
#include "gumbo-query/src/Selection.h"


bool MessageParser::parse(CNode& post)
{
    // parse author
    CSelection author = post.find("span.name > strong");
    if (author.nodeNum() < 1)
        return false;
    rawMessage.author=author.nodeAt(0).text();

    // parse message
    CSelection message = post.find(".postbody > div");
    if (message.nodeNum() < 1)
        return false;
    rawMessage.content = message.nodeAt(0).text();

    // parse date
    // TODO(arthur)
    CSelection  date= post.find(".postdetails");
    if (date.nodeNum() >= 2)
    if (date.nodeAt(1).childNum() >= 4)
    {
        rawMessage.date.fromString(
            date.nodeAt(1).childAt(3).text());
    }

    return true;
}

RawMessage MessageParser::toRaw()
{
    return rawMessage;
}
