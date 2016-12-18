/**
* HTTPDownloader.cpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 *
 * Written by Uli Köhler (techoverflow.net)
 * Published under CC0 1.0 Universal (public domain)
 */
#include "HTTPDownloader.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "fstream"
using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data << endl;
    return size * nmemb;
}

HTTPDownloader::HTTPDownloader() {
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader() {
    curl_easy_cleanup(curl);
}


#include <chrono>
#include <thread>

// This function is not part of HTTPDownloader.
// Made by ArthurSonzogni and the answer from
// http://stackoverflow.com/a/4059934
static std::string to_utf8(const std::string& text)
{
    std::string output;
    output.resize(2*text.size());
    const unsigned char *in =  (unsigned char*)&text[0];
         unsigned char *out =  (unsigned char*)&output[0];
    while (*in)
      if (*in<128) *out++=*in++;
      else *out++=0xc2+(*in>0xbf), *out++=(*in++&0x3f)+0x80;
    output.resize(out-(unsigned char*)output.c_str());
    return output;
}

// static
void make_cookie_file()
{
	static bool is_done = false;
	if (is_done)
		return;
	std::string cookie_file_content = 
R"(
.forumactif.com	TRUE	/	FALSE	1513599487	displayCookieConsent	y
.cbna.forumactif.com	TRUE	/	FALSE	1513599645	fa_cbna_forumactif_com_data	a%3A3%3A%7Bs%3A11%3A%22autologinid%22%3Bs%3A64%3A%2224ceb5277b3dcfac76d04ae09c8ec249c70e16fq24ceb528ed83f1e3142c0a8d%22%3Bs%3A6%3A%22userid%22%3Bs%3A4%3A%222483%22%3Bs%3A5%3A%22posts%22%3Ba%3A2%3A%7Bs%3A6%3A%22number%22%3Bi%3A0%3Bs%3A4%3A%22last%22%3Bi%3A0%3B%7D%7D
.cbna.forumactif.com	TRUE	/	FALSE	0	fa_cbna_forumactif_com_sid	a63c89037750a07999c81b60c8805ba3
.cbna.forumactif.com	TRUE	/	FALSE	0	fa_cbna_forumactif_com_t	a%3A1%3A%7Bi%3A13138%3Bi%3A1482063646%3B%7D
)";
	std::ofstream cookie_file("./cookieFile.txt");
	cookie_file << cookie_file_content << std::endl;
	is_done = true;
}

string HTTPDownloader::download(const std::string& url) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 100);
		//curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)");

		make_cookie_file();
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookieFile.txt");


    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }

    // sleep for 1s
    //std::this_thread::sleep_for (std::chrono::seconds(1));

 
    // NOTE(ArthurSonzogni)
    // we remove every line break.
    // I don't know why exactly.
    std::string str = out.str();
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

    // convert windows-1252 to UTF8
    return to_utf8(str);
}

