#ifndef USERPARSER_H
#define USERPARSER_H

#include "data/raw/RawUser.hpp"
#include "gumbo-query/src/Document.h"

class UserParser
{
    public:
        UserParser(const std::string& website);
        bool parse(const int user_id);
        RawUser toRaw();

        void reload(const std::string& directory);
    private:
        const std::string website;
        RawUser raw_user;
};

#endif /* end of include guard: USERPARSER_H */
