#ifndef TOPICPARSER_H
#define TOPICPARSER_H

#include "MessageParser.hpp"
#include "data/raw/RawTopic.hpp"
#include "gumbo-query/src/Document.h"

class HtmlToMarkdown;

class TopicParser {
 public:
  TopicParser(const std::string& website);
  bool parse(const int topic_id);
  RawTopic toRaw();

  void reload(const std::string& directory);

 private:
  const std::string website;
  RawTopic raw_topic;

  bool parseFirstPage(CDocument& doc);
};

#endif /* end of include guard: TOPICPARSER_H */
