/**
* HTTPDownloader.cpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 *
 * Written by Uli Köhler (techoverflow.net)
 * Published under CC0 1.0 Universal (public domain)
 */
#include "HTTPDownloader.hpp"
#include "./CP1252_to_UTF8.hpp"
#include <algorithm>
#include <chrono>
#include <curl/curl.h>
#include <curl/curlbuild.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
using namespace std::chrono_literals;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
  std::string data((const char*) ptr, (size_t) size * nmemb);
    *((std::stringstream*) stream) << data << std::endl;
    return size * nmemb;
}

HTTPDownloader::HTTPDownloader() {
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader() {
    curl_easy_cleanup(curl);
}

// static
void make_cookie_file()
{
  static bool is_done = false;
  if (is_done)
    return;
  while (!std::ifstream("./cookie.txt").good()) {
    std::cerr << "Please place a cookie file named \"cookie.txt\" in the current directory" << std::endl;
    std::cerr << R"(Download the cookies.txt from the Chrome Extension (https://chrome.google.com/webstore/detail/njabckikapfpffapmjgojcnbfjonfjfg))" << std::endl;
    std::string value;
    std::cout << "Done ?";
    std::cin >> value;
  }
  is_done = true;
}

std::string HTTPDownloader::download(const std::string& url, bool use_cookie) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); //Prevent "longjmp causes uninitialized stack frame" bug
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 100);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)");

    if (use_cookie) {
      make_cookie_file();
      curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookieFile.txt");
    }


    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }

    // Remove new lines.
    std::string str = out.str();
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

    std::cerr << " ... Waiting 3s ...\r" << std::flush;
    std::this_thread::sleep_for(3s);

    return CP1252_to_UTF8(str);
}
