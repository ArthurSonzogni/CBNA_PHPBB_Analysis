#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include "data/raw/RawMessage.hpp"
#include "gumbo-query/src/Node.h"

class MessageParser {
 public:
  bool parse(const std::string& document, CNode& post);
  RawMessage toRaw();

 private:
  RawMessage rawMessage;
};

#endif /* end of include guard: MESSAGEPARSER_H */
