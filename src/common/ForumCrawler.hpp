#ifndef FORUMCRAWLER_HPP
#define FORUMCRAWLER_HPP

#include "data/raw/RawForum.hpp"

class HtmlToMarkdown;

class ForumCrawler {
 public:
  ForumCrawler(const std::string& website,
               const std::string& save_dir);

  bool parse();
  void load();

  const RawForum& raw_forum();

 private:
  void load_users();
  void load_topics();
  bool parse_users();
  bool parse_topics();
  void save();
  void save_user(int user_id);
  void save_topic(int topic_id);

  RawForum rawForum;

  std::string website;
  std::string save_dir;
  int topic_next = 0;
  int user_next = 1;
};

#endif /* end of include guard: FORUMCRAWLER_HPP */
