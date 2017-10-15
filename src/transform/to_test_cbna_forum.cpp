#include "transform/CbnaHtmlToMarkdown.hpp"
#include "gumbo-query/src/Document.h"
#include "gumbo-query/src/Node.h"
#include "to_test_cbna_forum.hpp"
#include <fstream>

#include <iostream>

using JSON = nlohmann::json;

namespace {

static bool mkdir(const std::string& directory) {
  std::cout << ("mkdir -p " + directory) << std::endl;
  return std::system(("mkdir -p " + directory).c_str());
}

void format_labels(std::vector<std::string>& labels) {
  for (auto& label : labels) {
    for (auto& c : label) {
      c = std::tolower(c);
      if (c == ' ')
        c = '_';
    }
  }
}

std::map<std::string, std::vector<std::string>> topic_labels_map = {
    {"Le CBNA", {"CBNA"}},
    {"Projets", {"projet", "création"}},
    {"Projets communs", {"projet", "commun", "création"}},
    {"Compétitions", {"compétition"}},
    {"GMF: GameMaker en France", {"GMF"}},
    {"Zut", {"Zut"}},
    {"Section Membres", {"membres"}},
    {"CBN'ART", {"création", "art"}},
    {"Section Spirituelle", {"débat", "partage"}},
    {"Game Design", {"game_design"}},
    {"Game Maker", {"game_maker"}},
    {"Programmation", {"programmation"}},
    {"Entraide débutants", {"aide", "débutant"}},
    {"Entraide confirmés", {"aide", "confirmé"}},
    {"Scripts GML", {"scripts", "création", "GML"}},
    {"Apprendre à utiliser GameMaker", {"aide", "cours"}},
};

std::vector<std::string> topic_labels(const RawTopic& topic) {
  if (topic.path.size() != 3) {
    std::cerr << "Warning: no path for a topic" << std::endl;
    return {};
  }
  std::string section = topic.path[2];
  if (topic_labels_map.count(section) == 0)
    std::cerr << "Warning \"" << section << "\" is not found" << std::endl;
  return topic_labels_map[section];
}

struct ExtractLabelResult {
  std::string title;
  std::vector<std::string> labels;
};

ExtractLabelResult extract_labels(const std::string& text) {
  ExtractLabelResult result;
  bool in = false;
  std::string label;
  for (int i = 0; i < text.size(); ++i) {
    if (!in && text[i] == '[') {
      in = true;
      label = "";
      continue;
    }

    if (in && text[i] == ']') {
      in = false;
      result.labels.push_back(label);
      continue;
    }

    if (in) {
      label += text[i];
      continue;
    }

    result.title += text[i];
  }

  return result;
}
}

void to_test_cbna_forum(const RawForum& forum, const std::string& directory) {
  std::string user_directory = directory + "/message_board/users/";
  std::string topic_directory = directory + "/message_board/contents/topics/";
  mkdir(user_directory);
  mkdir(topic_directory);
  //-------------
  // Users
  //-------------
  for (auto& user_pair : forum.users) {
    auto& user_id = user_pair.first;
    auto& user = user_pair.second;

    std::string user_filename = user_directory + std::to_string(user_id);
    JSON user_json;
    user_json["email"] = "unknown";
    user_json["name"] = user.name;
    user_json["avatar"] = user.avatar_url;
    user_json["is_moderator"] = false;
    user_json["is_admin"] = false;
    user_json["signupdate"] = user.subscription_date;

    std::ofstream file(user_filename);
    file << std::setw(2) << user_json;
  }

  //-------------
  // Topics
  //-------------
  CbnaHtmlToMarkdown html_to_markdown;
  for (auto& topic_pair : forum.topics) {
    auto& topic_id = topic_pair.first;
    auto& topic = topic_pair.second;

    std::string topic_filename = topic_directory + std::to_string(topic_id);

    //-------------
    // Topic info
    //-----------
    std::ofstream file(topic_filename);
    JSON topic_json;
    topic_json["creation_date"] = "2016-01-01T00:00:00";
    // Quickfix, remove the first two char (0x22C2)
    // TODO(arthursonzogni): remove this once the bug is fixed.
    std::string title = topic.title.substr(2, topic.title.size() - 2);
    ExtractLabelResult extract_label_result = extract_labels(title);
    std::vector<std::string> labels = topic_labels(topic);
    labels.insert(labels.end(), extract_label_result.labels.begin(),
                  extract_label_result.labels.end());
    format_labels(labels);

    topic_json["title"] = extract_label_result.title;
    topic_json["labels"] = labels;

    //-------------
    // Messages
    //-------------
    topic_json["messages"] = JSON::array();
    int message_id = 0;
    for (auto& message : topic.messages) {
      JSON message_json;
      message_json["authors"].push_back(message.author);
      message_json["date"] = message.date.toString();
      CDocument message_content;
      message_content.parse(message.content);
      CNode message_content_node = message_content.find("div").nodeAt(0);
      message_json["content"] = html_to_markdown(message_content_node);
      std::cout << "content = " << html_to_markdown(message_content_node)
                << std::endl;
      topic_json["messages"].push_back(message_json);
      topic_json["creation_date"] = message.date.toString();
    }
    file << std::setw(2) << topic_json;
  }
}
