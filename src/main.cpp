#include "download/HTTPDownloader.hpp"
#include <iostream>
#include <string>


//#define HEADER_ACCEPT "Accept:text/html,application/xhtml+xml,application/xml"
//#define HEADER_USER_AGENT "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.70 Safari/537.17"

#include "gumbo-query/src/Document.h"
#include "gumbo-query/src/Node.h"


#include "parse/TopicParser.hpp"

int main(int argc, char** argv)
{
    TopicParser topicParser("cbna.forumactif.com");
    topicParser.parse(13368);
    return EXIT_SUCCESS;


    HTTPDownloader downloader;
		std::string content = downloader.download("http://cbna.forumactif.com/t13178p60-le-nouveau-cbna");
    //std::string content = downloader.download("http://arthursonzogni.com")
		//std::cout << "==================" << std::endl;
		//std::cout << "|  Content       |" << std::endl;
		//std::cout << "==================" << std::endl;
		//std::cout << content << std::endl;

		CDocument doc;
		doc.parse(content.c_str());

    // parse post
		CSelection post = doc.find(".post");
		for(int i = 0; i<post.nodeNum(); ++i)
    {
        std::cout << std::endl << "======================" << std::endl;

        // parse author
        CSelection author = post.nodeAt(i).find(".name");
        if (author.nodeNum())
        {
            std::cout << "[author]" << std::endl;
            std::cout << author.nodeAt(0).text() << std::endl << std::endl;; // some link
        }
        // parse message
        CSelection message = post.nodeAt(i).find(".postbody");
        if (message.nodeNum())
        {
            std::cout << "[message]" << std::endl;
            std::cout << message.nodeAt(0).text() << std::endl << std::endl;; // some link
        }
    }
}
