#ifndef TO_WORD_USAGE_H
#define TO_WORD_USAGE_H

#include "data/raw/RawForum.hpp"
#include "data/word_usage/WordUsage.hpp"

WordUsage to_word_usage(const RawForum& forum, std::set<std::string> word_to_view);

#endif /* end of include guard: TO_WORD_USAGE_H */
