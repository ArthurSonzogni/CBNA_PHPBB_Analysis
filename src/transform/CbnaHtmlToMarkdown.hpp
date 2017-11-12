#ifndef CBNAHTMLTOMARKDOWN_H
#define CBNAHTMLTOMARKDOWN_H

#include "transform/HtmlToMarkdown.hpp"

class CbnaHtmlToMarkdown : public HtmlToMarkdown {
 public:
  CbnaHtmlToMarkdown();
  virtual ~CbnaHtmlToMarkdown() = default;

  void PrintEmojiNotFound();
};

#endif /* end of include guard: CBNAHTMLTOMARKDOWN_H */
