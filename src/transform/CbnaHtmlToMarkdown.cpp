#include "transform/CbnaHtmlToMarkdown.hpp"
#include <map>
#include <regex>
#include <string>
#include <iostream>

namespace {

void translate_link_address(std::string& text) {
  std::smatch match;
  {
    std::regex regex(
        R"regex(^https?://cbna.forumactif.com(?:/.*)*/(.*)-t([0-9]+).*)regex");
    if (std::regex_match(text, match, regex)) {
      text = "#/forum/topic/" + match.str(2) + "-" + match.str(1);
      return;
    }
  }

  {
    std::regex regex(
        R"regex(^https?://cbna.forumactif.com(?:/.*)*/t([0-9]+)-([^.]*).*$)regex");
    if (std::regex_match(text, match, regex)) {
      text = "#/forum/topic/" + match.str(1) + "-" + match.str(2);
      return;
    }
  }
}

std::string special_tag_a(const HtmlToMarkdown& htmlToMarkdown, CNode node) {
  std::string text = htmlToMarkdown(node);
  std::string href = node.attribute("href");
  translate_link_address(text);
  translate_link_address(href);
  return "[" + text + "](" + href + ")";
}

std::map<std::string, int> emoji_not_found;

std::map<std::string, std::string> emoji = {
    //{"https://imgfast.net/users/3412/18/80/54/smiles/721883.png", ":heart:"},
    //{"https://imgfast.net/users/3412/18/80/54/smiles/922323.png", ":smiley:"},
};

std::string special_tag_img(const HtmlToMarkdown& htmlToMarkdown, CNode node) {
  std::string alt = node.attribute("alt");
  std::string src = node.attribute("src");

  auto my_emoji = emoji.find(src);
  if (my_emoji == emoji.end()) {
    emoji_not_found[src]++;
    return "![" + alt + "](" + src + ")";
  }
  else {
    return my_emoji->second;
  }
}

}  // namespace

CbnaHtmlToMarkdown::CbnaHtmlToMarkdown() {
  handlers["a"] = special_tag_a;
  handlers["img"] = special_tag_img;
}

void CbnaHtmlToMarkdown::PrintEmojiNotFound() {
  std::vector<std::pair<int, std::string>> list;
  for (const auto& it : emoji_not_found)
    list.push_back({it.second, it.first});
  sort(list.begin(), list.end());
  for (const auto& it : list) {
    std::cout << it.first << " -> " << it.second << std::endl;
  }
}
