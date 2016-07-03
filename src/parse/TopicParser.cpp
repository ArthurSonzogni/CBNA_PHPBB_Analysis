#include "TopicParser.hpp"
#include "download/HTTPDownloader.hpp"
#include "gumbo-query/src/Document.h"
#include "gumbo-query/src/Node.h"
#include "MessageParser.hpp"

#include <iostream>


TopicParser::TopicParser(const std::string& website):
    website(website)
{
}

bool TopicParser::parse(const int topic_id)
{
    raw_topic.messages.clear();
    for(int page = 0;;)
    {
        const std::string page_name = "http://" + website + "/t" + std::to_string(topic_id) + "p" + std::to_string(page) +  "-title";
        std::cout << "parsing : " << page_name << std::endl;

        // download the topic
        HTTPDownloader downloader;
        std::string content = downloader.download(page_name);

        if (content.empty()) break;

        // read all posts
        CDocument doc;
        doc.parse(content.c_str());

        // parse post
        CSelection post = doc.find(".post");
        bool nothing_found = true;
        for(int i = 0; i<post.nodeNum(); ++i)
        {
            auto node = post.nodeAt(i);
            MessageParser message_parser;
            if (message_parser.parse(node))
            {
                raw_topic.messages.push_back(message_parser.toRaw());
                ++page;
                nothing_found = false;
            }
        }

        if (nothing_found) break;
    }

    return raw_topic.messages.size();
}

RawTopic TopicParser::toRaw()
{
    return raw_topic;
}
