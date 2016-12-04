#include "MessageParser.hpp"
#include "gumbo-query/src/Selection.h"
#include "HTMLToMarkdown.h"


bool MessageParser::parse(CNode& post)
{
    // parse author
    CSelection author = post.find("span.name > strong");
    if (author.nodeNum() < 1)
        return false;
    rawMessage.author=author.nodeAt(0).text();

    // remove ads
    if (rawMessage.author == "Contenu sponsorisé")
      return false;

    // parse message
    CSelection message = post.find(".postbody > div");
    if (message.nodeNum() < 1)
        return false;
    rawMessage.content = HTMLToMarkdown(message.nodeAt(0));
    //std::cerr << "--------------------------" << std::endl;
    //std::cerr << rawMessage.content << std::endl;

    // parse date
    // TODO(arthur)
    CSelection  date= post.find(".postdetails");
    if (date.nodeNum() >= 2)
    if (date.nodeAt(1).childNum() >= 4)
    {
        rawMessage.date.fromString(date.nodeAt(1).childAt(3).text());
    }

    return true;
}

RawMessage MessageParser::toRaw()
{
    return rawMessage;
}
