#include "WordUsage.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

static void fix_word(std::string& word, int size)
{
    for(auto& c : word) if (c == '\n') c = ' ';
    if (word.size() > size) word.resize(size);
}

void WordUsage::add(const std::string& word,
                    const std::string& user,
                    const std::string& section)
{
    if (user == "Contenu sponsorisé") return;
    if (word.size() <= 3) return;
    sum++;
    sum_words[word]++;
    sum_users[user]++;
    sum_section[section]++;
    sum_user_words[user][word]++;
    sum_words_user[word][user]++;
    sum_section_users[section][user]++;
    sum_section_words[section][word]++;
}

void WordUsage::print_summary(std::ostream& out)
{
    out << std::endl << "[user best word]" << std::endl;
    print_user_best_word(out);
    out << std::endl << "[word best user]" << std::endl;
    print_word_best_user(out);
    out << std::endl << "[section]" << std::endl;
    print_section(out);
}

void WordUsage::print_word_best_user(std::ostream& out)
{
    struct RecordWord
    {
        std::string word;
        int64_t sum;
        bool operator<(const RecordWord& other) const
        {
            return sum>other.sum;
        }
    };
    std::vector<RecordWord> record_word;
    for(auto& e : sum_words)
    {
        if (e.first.size()>=8)
          record_word.push_back({e.first,e.second});
    }
    sort(record_word.begin(),record_word.end());

    if (record_word.size() > 500)
        record_word.resize(500);

    for(auto& element : record_word)
    {
        double best_ratio = 0.0;
        std::string best_user;
        for(auto& user_count : sum_words_user[element.word])
        {
            auto& user = user_count.first;
            auto sum_words = sum_users[user];
            if (sum_words*1000000<sum) continue;
            auto sum_this_word = user_count.second;
            double this_ratio = double(sum_this_word) / double(sum_words);
            if (this_ratio > best_ratio)
            {
                best_ratio = this_ratio;
                best_user = user;
            }
        }
        fix_word(element.word,20);
        fix_word(best_user,20);

        std::cout << " | " << std::setw(5)  << element.sum
                  << " | " << std::setw(20) << element.word
                  << " | " << std::setw(20) << best_user
                  << " | " << std::setw(20) << 100.0 * best_ratio  << "%"
                  << " | " << std::endl;

    }
}

void WordUsage::print_user_best_word(std::ostream& out)
{
    struct UserBestWord
    {
        std::string user;
        std::string word;
        double ratio;
        bool operator<(const UserBestWord& other) const
        {
            return ratio>other.ratio;
        }
    };
    std::vector<UserBestWord> user_best_word;
    for(const auto& by_user : sum_user_words)
    {
        const auto& user = by_user.first;
        if (sum_users[user]*1000000.0 < sum) continue;
        std::string best_word = "";
        int64_t best_count = 0;
        for(const auto&  by_word : by_user.second)
        {
            if (by_word.second > best_count)
            {
                best_word = by_word.first;
                best_count = by_word.second;
            }
        }
        double ratio = double(best_count)/double(sum_users[user]);
        user_best_word.push_back(UserBestWord{user,best_word,ratio});
    }
    sort(user_best_word.begin(),user_best_word.end());
    if (user_best_word.size() > 500)
        user_best_word.resize(500);
    for(auto& u : user_best_word)
    {
        fix_word(u.word,20);
        fix_word(u.user,20);

        out << " | " << std::setw(22) << u.user
            << " | " << std::setw(20)  << u.word
            << " | " << std::setw(10)  << int(10000*u.ratio) * 0.01 << "%"
            << " | " << std::endl;
    }
}

void WordUsage::print_section(std::ostream& out)
{
    for(auto& it : sum_section)
    {
        std::string section = it.first;
        double ratio = double(it.second) / double(sum);
        fix_word(section,50);
        out << " | " << std::setw(50) << section
            << " | " << std::setw(10) << int(10000*ratio)/100.0 << "%"
            << std::endl;
    }
}
