#ifndef WORDUSAGE_H
#define WORDUSAGE_H

#include <string>
#include <map>
#include <ostream>

struct WordUsage
{
    //-------------------------------------------------------------------------

    void add(const std::string& word,
             const std::string& user,
             const std::string& section);
    void print_summary(std::ostream& out);

    //-------------------------------------------------------------------------

    // Here we store sum relatively to some variables in {word,user,section}
    int64_t                                              sum;
    std::map<std::string,int64_t>                        sum_words;
    std::map<std::string,int64_t>                        sum_users;
    std::map<std::string,int64_t>                        sum_section;
    std::map<std::string,std::map<std::string,int64_t>>  sum_user_words;
    std::map<std::string,std::map<std::string,int64_t>>  sum_words_user;
    std::map<std::string,std::map<std::string,int64_t>>  sum_section_users;
    std::map<std::string,std::map<std::string,int64_t>>  sum_section_words;

    //-------------------------------------------------------------------------
private:
    void print_user_best_word(std::ostream& out);
    void print_word_best_user(std::ostream& out);
    void print_section(std::ostream& out);
};

#endif /* end of include guard: WORDUSAGE_H */
