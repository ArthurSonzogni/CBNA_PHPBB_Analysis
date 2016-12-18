#include "UserParser.hpp"
#include "download/HTTPDownloader.hpp"
#include "gumbo-query/src/Document.h"
#include "gumbo-query/src/Node.h"
#include "UserParser.hpp"

#include <iostream>

const std::string title_selector        = "#emptyidcc > table > tbody > tr > td:nth-child(2) > table.forumline > tbody > tr:nth-child(1) > th > h1";
const std::string avatar_selector       = "#emptyidcc > table > tbody > tr > td:nth-child(2) > table.forumline > tbody > tr:nth-child(3) > td:nth-child(1) > table > tbody > tr:nth-child(1) > td:nth-child(2) > b > span > img";
const std::string subscription_selector = "#field_id-4 > td:nth-child(2) > div > div";
const std::string age_selector          = "#field_id-5 > td:nth-child(2) > div > div";
const std::string message_count_selector= "#field_id-6 > td:nth-child(2) > div > div";
const std::string hobbies_selector      = "#field_id-8 > td:nth-child(2) > div > div";
const std::string job_or_study_selector = "#field_id-9 > td:nth-child(2) > div > div";
const std::string localisation_selector = "#field_id-11 > td:nth-child(2) > div > div";

static bool read_selector_string(CDocument& document,
                                 const std::string& selector,
                                 std::string& value) {
	CSelection selection = document.find(selector);
	if (selection.nodeNum() != 1)
		return false;
	value = selection.nodeAt(0).text();	
		return true;
}

static bool read_selector_int(CDocument& document,
                                 const std::string& selector,
                                 int& value) {
	CSelection selection = document.find(selector);
	if (selection.nodeNum() != 1)
		return false;
	value = std::stoi(selection.nodeAt(0).text());
}

UserParser::UserParser(const std::string& website):
    website(website)
{
}

bool UserParser::parse(const int user_id)
{
		raw_user = RawUser();
    const std::string page_name = "http://" + website + "/u" + std::to_string(user_id);

    // download the topic
    HTTPDownloader downloader;
    std::string content = downloader.download(page_name);

    if (content.empty())
      return false;

    // parse the document
    CDocument doc;
    doc.parse(content.c_str());

    // parse title
		{
			CSelection selection = doc.find("title");
			if (selection.nodeNum() != 1)
				return false;
			raw_user.name = selection.nodeAt(0).text();
			std::string remove_prefix = "Voir un profil - ";
			std::string::size_type pos = raw_user.name.find(remove_prefix);
			if (pos == std::string::npos)
				return false;
			raw_user.name.erase(pos, remove_prefix.length());
		}

		// parse avatar
		{
			CSelection selection = doc.find(avatar_selector);
			if (selection.nodeNum() != 1)
				return false;
			raw_user.avatar_url = selection.nodeAt(0).attribute("src");
		}

		// parse other data
		read_selector_string(doc, subscription_selector, raw_user.subscription_date);
		read_selector_string(doc, age_selector, raw_user.subscription_date);
		read_selector_int(doc, message_count_selector, raw_user.message_count);
		read_selector_string(doc, hobbies_selector, raw_user.hobbies);
		read_selector_string(doc, job_or_study_selector, raw_user.job_or_study);
		read_selector_string(doc, localisation_selector, raw_user.localisation);
		

		//RawUser::JSON json;
		//raw_user.write(json);
		//std::cout << json.dump(2) << std::endl;
		std::cout << user_id << " | " << raw_user.name << std::endl;
		return true;
}

RawUser UserParser::toRaw()
{
    return raw_user;
}
