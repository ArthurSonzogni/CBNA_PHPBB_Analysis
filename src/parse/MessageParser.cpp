#include "MessageParser.hpp"
#include "gumbo-query/src/Document.h"
#include "gumbo-query/src/Selection.h"

#include <iostream>

bool MessageParser::parse(const std::string& document, CNode& post) {

  // Parse message.
  CSelection message = post.find(".postbody > div");
  if (message.nodeNum() < 1) {
    return false;
  }

  CNode message_node = message.nodeAt(0);
  rawMessage.content = document.substr(
      message_node.startPosOuter(),
      message_node.endPosOuter() - message_node.startPosOuter());

  // Parse author.
  CSelection author = post.find("span.name > strong > a");
  if (author.nodeNum() == 0) {
    return false;
  }
  std::string author_href = author.nodeAt(0).attribute("href");
  if (author_href.size() <= 2) {
    return false;
  }
  rawMessage.author = std::stoi(author_href.substr(2, std::string::npos));

  // Parse date.
  // TODO(arthur)
  CSelection date = post.find(".postdetails");
  if (date.nodeNum() >= 2) {
    if (date.nodeAt(1).childNum() >= 4) {
      rawMessage.date.fromString(date.nodeAt(1).childAt(3).text());
    }
  }

  return true;
}

RawMessage MessageParser::toRaw() {
  return rawMessage;
}
