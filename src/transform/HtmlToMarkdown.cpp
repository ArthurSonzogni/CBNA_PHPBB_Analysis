#include "HtmlToMarkdown.hpp"
#include <sstream>

HtmlToMarkdown::HtmlToMarkdown() {
  handlers["a"] = &HtmlToMarkdown::tag_a;
  handlers["br"] = &HtmlToMarkdown::tag_br;
  handlers["dd"] = &HtmlToMarkdown::tag_dd;
  handlers["div"] = &HtmlToMarkdown::tag_div;
  handlers["h1"] = &HtmlToMarkdown::tag_h1;
  handlers["h2"] = &HtmlToMarkdown::tag_h2;
  handlers["h3"] = &HtmlToMarkdown::tag_h3;
  handlers["h4"] = &HtmlToMarkdown::tag_h4;
  handlers["h5"] = &HtmlToMarkdown::tag_h5;
  handlers["h6"] = &HtmlToMarkdown::tag_h6;
  handlers["hr"] = &HtmlToMarkdown::tag_hr;
  handlers["i"] = &HtmlToMarkdown::tag_i;
  handlers["iframe"] = &HtmlToMarkdown::tag_iframe;
  handlers["img"] = &HtmlToMarkdown::tag_img;
  handlers["li"] = &HtmlToMarkdown::tag_li;
  handlers["li"] = &HtmlToMarkdown::tag_li;
  handlers["p"] = &HtmlToMarkdown::tag_p;
  handlers["strong"] = &HtmlToMarkdown::tag_strong;
}

std::string HtmlToMarkdown::operator()(CNode node) const {
  return content(node);
}

std::string HtmlToMarkdown::content(CNode node) const {
  if (node.childNum() == 0)
    return node.text();

  std::string result;
  for (unsigned int i = 0; i < node.childNum(); ++i) {
    result += dispatch(node.childAt(i));
  }
  return result;
}

std::string HtmlToMarkdown::dispatch(CNode node) const {
  auto handler = handlers.find(node.tag());

  if (handler == handlers.end())
    return tag_other(node);

  return handler->second(*this, node);
}

std::string HtmlToMarkdown::tag_other(CNode node) const {
  return content(node);
}

std::string HtmlToMarkdown::tag_p(CNode node) const {
  return content(node) + "\n\n";
}

std::string HtmlToMarkdown::tag_br(CNode node) const {
  return "\n";
}

std::string HtmlToMarkdown::tag_strong(CNode node) const {
  return "**" + content(node) + "**";
}

std::string HtmlToMarkdown::tag_strike(CNode node) const {
  return "~~" + content(node) + "~~";
}

std::string HtmlToMarkdown::tag_i(CNode node) const {
  return "*" + content(node) + "*";
}

std::string HtmlToMarkdown::tag_a(CNode node) const {
  return "[" + content(node) + "](" + node.attribute("href") + ")";
}

std::string HtmlToMarkdown::tag_li(CNode node) const {
  return " * " + content(node);
}

std::string HtmlToMarkdown::tag_img(CNode node) const {
  return "![" + node.attribute("alt") + "](" + node.attribute("src") + ")";
}

std::string HtmlToMarkdown::tag_h1(CNode node) const {
  return "# " + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_h2(CNode node) const {
  return "## " + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_h3(CNode node) const {
  return "### " + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_h4(CNode node) const {
  return "#### " + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_h5(CNode node) const {
  return "##### " + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_h6(CNode node) const {
  return "###### " + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_dd_code(CNode node) const {
  return "\n```" + content(node) + "```\n";
}

std::string HtmlToMarkdown::tag_dd_spoiler(CNode node) const {
  std::istringstream ss(content(node));
  std::string line;
  std::string result = "\n";
  while (std::getline(ss, line)) {
    if (line.size())
      result += ">! " + line;
  }
  return result + "\n\n";
}

std::string HtmlToMarkdown::tag_dd_other(CNode node) const {
  std::istringstream ss(content(node));
  std::string line;
  std::string result = "\n";
  while (std::getline(ss, line)) {
    if (line.size())
      result += "> " + line;
  }
  return result + "\n\n";
}

std::string HtmlToMarkdown::tag_dd(CNode node) const {
  if (node.attribute("class") == "quote")
    return tag_dd_other(node);
  else if (node.attribute("class") == "code")
    return tag_dd_code(node);
  else if (node.attribute("class") == "spoiler_closed")
    return "";
  else
    return tag_dd_spoiler(node);
}

std::string HtmlToMarkdown::tag_div(CNode node) const {
  return "\n" + content(node) + "\n";
}

std::string HtmlToMarkdown::tag_hr(CNode node) const {
  return "\n---\n";
}

std::string HtmlToMarkdown::tag_iframe(CNode node) const{
  std::string src = node.attribute("src");

  // try to parse youtube video
  static std::string youtube = "https://www.youtube.com/embed/";
  if (src.find(youtube) != std::string::npos) {
    src.erase(0, youtube.size());
    return "**Video:**\n[![Youtube Video](http://img.youtube.com/vi/" + src +
           "/0.jpg)](http://www.youtube.com/watch?v=" + src + ")";
  }

  // try to parse dailymotion video
  static std::string dailymotion = "http://www.dailymotion.com/embed/video/";
  if (src.find(dailymotion) != std::string::npos) {
    src.erase(0, dailymotion.size());
    return "**Video:**\n[![Dailymotion "
           "Video](http://www.dailymotion.com/thumbnail/320x240/video/" +
           src + ")](http://dai.ly/" + src + ")";
  }

  return "an iframe";
}
