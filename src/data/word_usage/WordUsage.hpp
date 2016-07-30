#ifndef WORDUSAGE_H
#define WORDUSAGE_H

#include <string>
#include <map>
#include <set>
#include <ostream>

struct WordUsage
{
    //-------------------------------------------------------------------------
    void add_word_to_view(const std::string& word);

    void add(const std::string& word,
             const std::string& user,
             const std::string& section);
    void print_summary(std::ostream&);
    void print_user_best_word(std::ostream& out);
    void print_word_best_user(std::ostream& out);
    void print_section(std::ostream& out);
    void print_word_to_view(std::ostream& out);

    //-------------------------------------------------------------------------

    // Here we store sum relatively to some variables in {word,user,section}
    int64_t                                              sum = 0;
    std::map<std::string,int64_t>                        sum_words;
    std::map<std::string,int64_t>                        sum_users;
    std::map<std::string,int64_t>                        sum_section;
    std::map<std::string,std::map<std::string,int64_t>>  sum_user_words;
    std::map<std::string,std::map<std::string,int64_t>>  sum_words_user;
    std::map<std::string,std::map<std::string,int64_t>>  sum_section_users;
    std::map<std::string,std::map<std::string,int64_t>>  sum_section_words;
    std::map<std::string,std::map<std::string,int64_t>>  sum_word_to_view_users;

    //-------------------------------------------------------------------------
private:
    
    std::set<std::string> word_to_view;
};

#endif /* end of include guard: WORDUSAGE_H */
