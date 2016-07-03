#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include "gumbo-query/src/Node.h"
#include "data/raw/RawMessage.hpp"


class MessageParser
{
    public:
        bool parse(CNode& post);
        RawMessage toRaw(); 
    private:
        RawMessage rawMessage;
};

#endif /* end of include guard: MESSAGEPARSER_H */
