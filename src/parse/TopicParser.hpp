#ifndef TOPICPARSER_H
#define TOPICPARSER_H

#include "data/raw/RawTopic.hpp"

class TopicParser
{
    public:
        TopicParser(const std::string& website);
        bool parse(const int topic_id);
        RawTopic toRaw();
    private:
        const std::string website;
        RawTopic raw_topic;
};

#endif /* end of include guard: TOPICPARSER_H */
