#include "HTMLToMarkdown.h"
#include <sstream>

namespace
{
  std::string content(CNode node);

  //--------------------------------------------
  // Parse a <tag>...</tag>
  //--------------------------------------------
  std::string tag_other(CNode node)
  {
    return content(node);
  }

  std::string tag_p(CNode node)
  {
    return content(node) + "\n\n";
  }

  std::string tag_br(CNode node)
  {
    return "\n";
  }

  std::string tag_strong(CNode node)
  {
    return "**" + content(node) + "**";
  }

  std::string tag_strike(CNode node)
  {
    return "~~" + content(node) + "~~";
  }

  std::string tag_i(CNode node)
  {
    return "*" + content(node) + "*";
  }

  std::string tag_a(CNode node)
  {
    return "[" + content(node) + "](" + node.attribute("href") + ")";
  }

  std::string tag_li(CNode node)
  {
    return " * " + content(node);
  }

  std::string tag_img(CNode node)
  {
    return "![" + node.attribute("alt") + "](" + node.attribute("src") + ")";
  }

  std::string tag_hn(CNode node, int n)
  {
    std::string prefix; while(n--) prefix += "#";
    return prefix + " " + content(node) + "\n";
  }

  std::string tag_dd_code(CNode node)
  {
    return "\n```" + content(node) + "```\n";
  }

  std::string tag_dd_spoiler(CNode node)
  {
    std::istringstream ss(content(node));
    std::string line;
    std::string result = "\n";
    while(std::getline(ss,line))
    {
      if (line.size())
        result += ">! " + line;
    }
    return result + "\n\n";
  }

  std::string tag_dd_other(CNode node)
  {
    std::istringstream ss(content(node));
    std::string line;
    std::string result = "\n";
    while(std::getline(ss,line))
    {
      if (line.size())
        result += "> " + line;
    }
    return result + "\n\n";
  }

  std::string tag_dd(CNode node)
  {
    if      (node.attribute("class") == "quote") return tag_dd_other(node);
    else if (node.attribute("class") == "code")  return tag_dd_code(node);
    else if (node.attribute("class") == "spoiler_closed")  return "";
    else                                         return tag_dd_spoiler(node);
  }

  std::string tag_div(CNode node)
  {
    return "\n" + content(node) + "\n";
  }

  std::string tag_hr(CNode node)
  {
    return "\n---\n";
  }

  std::string tag_iframe(CNode node)
  {
    std::string src=node.attribute("src");
    
    // try to parse youtube video
    static std::string youtube = "https://www.youtube.com/embed/";
    if (src.find(youtube) != std::string::npos)
    {
			src.erase(0,youtube.size());	
      return "**Video:**\n[![Youtube Video](http://img.youtube.com/vi/" + src + "/0.jpg)](http://www.youtube.com/watch?v=" + src + ")";
    }

		// try to parse dailymotion video 
    static std::string dailymotion = "http://www.dailymotion.com/embed/video/";
    if (src.find(dailymotion) != std::string::npos)
    {
			src.erase(0,dailymotion.size());	
		  return "**Video:**\n[![Dailymotion Video](http://www.dailymotion.com/thumbnail/320x240/video/" + src + ")](http://dai.ly/" + src +")";
    }

		return "an iframe";
  }

  //--------------------------------------------
  // Recursive machinery
  //--------------------------------------------
  std::string dispatch(CNode node)
  {
    std::string tag = node.tag();
    if      (tag == "p")      return tag_p(node);
    else if (tag == "br")     return tag_br(node);
    else if (tag == "strong") return tag_strong(node);
    else if (tag == "i")      return tag_i(node);
    else if (tag == "a")      return tag_a(node);
    else if (tag == "img")    return tag_img(node);
    else if (tag == "li")     return tag_li(node);
    else if (tag == "h1")     return tag_hn(node,1);
    else if (tag == "h2")     return tag_hn(node,2);
    else if (tag == "h3")     return tag_hn(node,3);
    else if (tag == "h4")     return tag_hn(node,4);
    else if (tag == "strike") return tag_strike(node);
    else if (tag == "dd")     return tag_dd(node);
    else if (tag == "div")    return tag_div(node);
    else if (tag == "hr")     return tag_hr(node);
    else if (tag == "iframe") return tag_iframe(node);
    else                      return tag_other(node);
  }

  std::string content(CNode node)
  {
    if (unsigned int n = node.childNum())
    {
      std::string result;
      for(unsigned int i = 0; i<n; ++i)
      {
        result += dispatch(node.childAt(i));
      }
      return result;
    }
    else
    {
      return node.text();
    }
  }

}

std::string HTMLToMarkdown(CNode node)
{
  return dispatch(node);
}

