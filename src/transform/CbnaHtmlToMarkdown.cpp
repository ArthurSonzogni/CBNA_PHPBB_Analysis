#include "transform/CbnaHtmlToMarkdown.hpp"
#include <regex>

namespace {

void translate(std::string& text) {
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
  translate(text);
  translate(href);
  return "[" + text + "](" + href + ")";
}

}  // namespace

CbnaHtmlToMarkdown::CbnaHtmlToMarkdown() {
  handlers["a"] = special_tag_a;
}
