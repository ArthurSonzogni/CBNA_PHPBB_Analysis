#include "MessageParser.hpp"
#include "gumbo-query/src/Selection.h"


bool MessageParser::parse(CNode& post)
{
    // parse author
    CSelection author = post.find("span.name > strong");
    if (author.nodeNum() < 1)
    {
        //std::cout << "Error at " << __LINE__ << std::endl;
        return false;
    }
    rawMessage.author=author.nodeAt(0).text();

    // parse message
    CSelection message = post.find(".postbody > div");
    if (message.nodeNum() < 1)
    {
        //std::cout << "Error at " << __LINE__ << std::endl;
        return false;
    }
    rawMessage.content = message.nodeAt(0).text();

    // parse date
    // TODO(arthur)
    //CSelection  date= post.find(".postdetails");
    //if (date.nodeNum() >= 2)
    //{
        ////std::cout << "Error at " << __LINE__ << std::endl;
        //std::cout << date.nodeAt(1).text() << std::endl;
        //return false;
    //}

    return true;
}

RawMessage MessageParser::toRaw()
{
    return rawMessage;
}
