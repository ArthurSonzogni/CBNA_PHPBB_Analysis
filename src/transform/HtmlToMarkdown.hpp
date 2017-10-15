#ifndef HTMLTOMARKDOWN_H
#define HTMLTOMARKDOWN_H

#include "gumbo-query/src/Node.h"
#include <string>
#include <functional>
#include <map>

class HtmlToMarkdown {
 public:
  HtmlToMarkdown();
  virtual ~HtmlToMarkdown() = default;
  std::string operator()(CNode node) const;

 protected:
  using Handler = std::function<std::string(const HtmlToMarkdown&, CNode)>;
  std::map<std::string, Handler> handlers;

  std::string content(CNode node) const;
  std::string dispatch(CNode node) const;
  std::string tag_a(CNode node) const;
  std::string tag_br(CNode node) const;
  std::string tag_dd(CNode node) const;
  std::string tag_dd_code(CNode node) const;
  std::string tag_dd_other(CNode node) const;
  std::string tag_dd_spoiler(CNode node) const;
  std::string tag_div(CNode node) const;
  std::string tag_h1(CNode node) const;
  std::string tag_h2(CNode node) const;
  std::string tag_h3(CNode node) const;
  std::string tag_h4(CNode node) const;
  std::string tag_h5(CNode node) const;
  std::string tag_h6(CNode node) const;
  std::string tag_hr(CNode node) const;
  std::string tag_i(CNode node) const;
  std::string tag_iframe(CNode node) const;
  std::string tag_img(CNode node) const;
  std::string tag_li(CNode node) const;
  std::string tag_other(CNode node) const;
  std::string tag_p(CNode node) const;
  std::string tag_strike(CNode node) const;
  std::string tag_strong(CNode node) const;
};

#endif /* end of include guard: HTMLTOMARKDOWN_H */
