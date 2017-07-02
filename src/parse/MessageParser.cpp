#include "MessageParser.hpp"
#include "HTMLToMarkdown.h"
#include "gumbo-query/src/Selection.h"

bool MessageParser::parse(CNode &post) {
  // parse author
  CSelection author = post.find("span.name > strong > a");
  if (author.nodeNum() == 0)
    return false;
  std::string author_href = author.nodeAt(0).attribute("href");
  if (author_href.size() <= 2)
    return false;
  rawMessage.author = std::stoi(author_href.substr(2, std::string::npos));

  // parse message
  CSelection message = post.find(".postbody > div");
  if (message.nodeNum() < 1)
    return false;
  rawMessage.content = HTMLToMarkdown(message.nodeAt(0));

  // parse date
  // TODO(arthur)
  CSelection date = post.find(".postdetails");
  if (date.nodeNum() >= 2)
    if (date.nodeAt(1).childNum() >= 4) {
      rawMessage.date.fromString(date.nodeAt(1).childAt(3).text());
    }

  return true;
}

RawMessage MessageParser::toRaw() { return rawMessage; }
