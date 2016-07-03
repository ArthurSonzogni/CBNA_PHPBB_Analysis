#include "MessageParser.hpp"
#include "gumbo-query/src/Selection.h"


// TODO rm
#include <iostream>


bool MessageParser::parse(CNode& post)
{
    // parse author
    CSelection author = post.find(".name");
    if (author.nodeNum() != 1) return false;
    rawMessage.author=author.nodeAt(0).text();

    // parse message
    CSelection message = post.find(".postbody");
    if (message.nodeNum() != 1) return false;
    rawMessage.content = message.nodeAt(0).text();

    return true;
}

RawMessage MessageParser::toRaw()
{
    //std::cout << "==== message ====" << std::endl;
    //std::cout << rawMessage.content << std::endl;
    return rawMessage;
}
