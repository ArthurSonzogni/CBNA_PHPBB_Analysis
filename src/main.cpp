#include "download/HTTPDownloader.hpp"
#include <iostream>
#include <string>


//#define HEADER_ACCEPT "Accept:text/html,application/xhtml+xml,application/xml"
//#define HEADER_USER_AGENT "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.70 Safari/537.17"

#include "gumbo-query/src/Document.h"
#include "gumbo-query/src/Node.h"


#include "parse/ForumParser.hpp"

int main(int argc, char** argv)
{
    ForumParser forumParser("cbna.forumactif.com");
    forumParser.parse();
    return EXIT_SUCCESS;
}
