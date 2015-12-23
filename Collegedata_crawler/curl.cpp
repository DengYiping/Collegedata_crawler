//
//  curl.cpp
//  Collegedata_crawler
//
//  Created by Scott Deng on 12/21/15.
//  Copyright © 2015 Scott Deng. All rights reserved.
//

#include "curl.hpp"


namespace curl{
  using namespace raw;
  
  static size_t curl_writer(char *data, size_t size, size_t nmemb, std::string *writerData)
  {
    auto realsize = size * nmemb;
    if (realsize <= 0) return 0;
    writerData->append(data);
    return realsize;
  } //curl writer for data buffer
  
  Curl::Curl(const std::string& url, const std::string& cookie){
    URL = url;
    COOKIE = cookie;
    handle = curl_easy_init();
    if(!handle) goto errors;
    
    CURLcode code;
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT,5L);
    if(code != CURLE_OK) goto errors;
    
    //code = curl_easy_setopt(handle, CURLOPT_USERAGENT,"Mozilla/5.0 (SymbianOS/9.4; Series60/5.0 Nokia5233/21.1.004; Profile/MIDP-2.1 Configuration/CLDC-1.1 ) AppleWebKit/525 (KHTML, like Gecko) Version/3.0 //BrowserNG/7.2.5.2 3gpp-gba");
    if(code != CURLE_OK) goto errors;
    
    //useragent
    code = curl_easy_setopt(handle,CURLOPT_FOLLOWLOCATION, 1L);
    if(code != CURLE_OK) goto errors;
    
    code = curl_easy_setopt(handle, CURLOPT_VERBOSE,0L);
    if(code != CURLE_OK) goto errors;
    //verbose mode disabled: enable if in debug
    
    code = curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, curl_writer);
    if(code != CURLE_OK) goto errors;
    return;
  errors:
    fprintf(stderr, "error in initialize curl\n");
    return;
  }//Curl::Curl
  
  
  std::unique_ptr<std::string> Curl::get(const std::string& url, const std::string& cookie){
    CURLcode code = CURLE_OK;
    std::unique_ptr<std::string> buffer_ptr(new std::string);
    
    code = curl_easy_setopt(handle, CURLOPT_COOKIE, cookie.c_str());
    if(code != CURLE_OK) goto errors;
    //cookie: third argument as char*
    
    
    //pass writer function
    code = curl_easy_setopt(handle, CURLOPT_WRITEDATA, buffer_ptr.get());
    if(code != CURLE_OK) goto errors;

    
    code = curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    if(code != CURLE_OK) goto errors;
    
    curl_easy_perform(handle);
    return buffer_ptr;
  errors:
    std::unique_ptr<std::string> error_ptr(new std::string);
    fprintf(stderr, "error in perform curl\n");
    return error_ptr;
  }//Curl::get
  
  std::unique_ptr<std::string> Curl::post(const std::string &post){
    CURLcode code = CURLE_OK;
    code = curl_easy_setopt(handle, CURLOPT_POST, 1);
    code = curl_easy_setopt(handle, CURLOPT_POSTFIELDS, post.c_str());
    if(code != CURLE_OK){
      fprintf(stderr, "error in set post data\n");
      return std::unique_ptr<std::string>();
    }
    else
      return get();
  }
}