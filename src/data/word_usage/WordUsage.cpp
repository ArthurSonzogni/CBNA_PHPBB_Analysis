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
    if (word.size() <= 2) return;
    std::string w = word;
    std::transform(w.begin(), w.end(), w.begin(), ::tolower);
    sum++;
    sum_words[w]++;
    sum_users[user]++;
    sum_section[section]++;
    sum_user_words[user][w]++;
    sum_words_user[w][user]++;
    sum_section_users[section][user]++;
    sum_section_words[section][w]++;

    if (word_to_view.count(w))
        sum_word_to_view_users[w][user]++;
}

void WordUsage::add_word_to_view(const std::string& word)
{
    std::string w = word;
    std::transform(w.begin(), w.end(), w.begin(), ::tolower);
    word_to_view.insert(w);
}

void WordUsage::print_summary(std::ostream& out)
{
    out << std::endl << "[user best word]" << std::endl;
    print_user_best_word(out);
    out << std::endl << "[word best user]" << std::endl;
    print_word_best_user(out);
    out << std::endl << "[section]" << std::endl;
    print_section(out);
    out << std::endl << "[word to view]" << std::endl;
    print_word_to_view(out);
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
        record_word.push_back({e.first,e.second});
    }
    sort(record_word.begin(),record_word.end());

    int limit = 0;
    while(limit<record_word.size() && record_word[limit].sum > 100)
      ++limit;
    out << "limit = " << limit << std::endl;
    if (record_word.size() > limit)
        record_word.resize(limit);

    for(auto& element : record_word)
    {
        double best_ratio = 0.0;
        std::string best_user;
        for(auto& user_count : sum_words_user[element.word])
        {
            auto& user = user_count.first;
            auto sum_words = sum_users[user];
            if (sum_words*500<sum) continue;
            auto sum_this_word = user_count.second;
            double this_ratio = double(sum_this_word) / double(sum_words);
            if (this_ratio > best_ratio)
            {
                best_ratio = this_ratio;
                best_user = user;
            }
        }
        if (best_user.size() == 0) continue;
        fix_word(element.word,20);
        fix_word(best_user,20);

        out << " | " << std::setw(5)  << element.sum
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
        if (sum_users[user]*50000 < sum) continue;
        std::string best_word = "";
        int64_t best_count = 0;
        for(const auto&  by_word : by_user.second)
        {
            if (by_word.first.size() > 6)
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
    for(auto& u : user_best_word)
    {
        fix_word(u.word,20);
        fix_word(u.user,20);

        out << " | " << std::setw(22) << u.user
            << " | " << std::setw(20)  << u.word
            << " | " << std::setw(10)  << int(10000.0*u.ratio) * 0.01 << "%"
            << " | " << std::endl;
    }
}

void WordUsage::print_section(std::ostream& out)
{
    struct SectionUsage
    {
        std::string section;
        double ratio;
        bool operator<(const SectionUsage& other) const
        {
            return  ratio > other.ratio;
        }
    };
    std::vector<SectionUsage> usages;

    for(auto& it : sum_section)
    {
        std::string section = it.first;
        double ratio = double(it.second) / double(sum);
        if (ratio>0.005)
        {
            fix_word(section,50);
            usages.push_back(SectionUsage{section,ratio});
        }
    }
    sort(usages.begin(),usages.end());
    for(auto& usage : usages)
    {
        out << " | " << std::setw(50) << usage.section
            << " | " << std::setw(10) << int(10000.0*usage.ratio)/100.0 << "%"
            << std::endl;
    }
}

void WordUsage::print_word_to_view(std::ostream& out)
{
    for(auto& word : word_to_view)
    {
        out << "  [ word = " << word << " ]"<< std::endl;
        struct UserCount
        {
            std::string user;
            int64_t count;
            bool operator<(const UserCount& other)
            {
                return count>other.count;
            }
        };
        std::vector<UserCount> data;
        for(auto& it : sum_word_to_view_users[word])
            data.push_back(UserCount{it.first,it.second});
        sort(data.begin(),data.end());
        for(auto& it : data)
        {
            fix_word(it.user,30);
            out << " | "  << std::setw(30) << it.user
                << " | "  << std::setw(5)  << it.count
                << " | "  << std::endl;
        }
    }
}
