//
//  curl.hpp
//  Collegedata_crawler
//
//  Created by Scott Deng on 12/21/15.
//  Copyright © 2015 Scott Deng. All rights reserved.
//

#ifndef curl_hpp
#define curl_hpp

#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <memory>
namespace curl{
  inline void init(){
    curl_global_init(CURL_GLOBAL_ALL);
  }//global initialization
  
  inline void cleanup(){
    curl_global_cleanup();
    return;
  }//global cleanup
  
  class Curl{
  private:
    CURL* handle;
    std::string URL;
    std::string COOKIE;

  public:
    Curl();//default setup
    
    inline Curl(const std::string& url, const std::string& cookie){
      *this = Curl();
      URL = url;
      COOKIE = cookie;
    }//initialized setup
    
    inline Curl(const std::string& url){
      *this = Curl();
      URL = url;
      COOKIE = "";
    }//initialized setup
    
    inline Curl(const Curl& right){
      *this = Curl();
      URL = right.URL;
      COOKIE = right.COOKIE;
    } //copy constructor
    
    inline Curl(Curl&& right): URL(right.URL), COOKIE(right.COOKIE), handle(right.handle){
      right.handle = NULL;
    } // move constructor
    
    inline void operator=(const Curl& right){
      URL = right.URL;
      COOKIE = right.URL;
    } //copy
    
    inline void operator=(Curl&& right){
      URL = right.URL;
      COOKIE = right.COOKIE;
      
      handle = right.handle;
      right.handle = NULL;
      
    } //move
    
    std::unique_ptr<std::string> get(const std::string& url, const std::string& cookie);
    inline std::unique_ptr<std::string> get(){
      return get(URL,COOKIE);
    }
    inline std::unique_ptr<std::string> get(const std::string& url){
      return get(url,COOKIE);
    }
    
    inline void set_url(const std::string& url){
      URL = url;
    }//change url
    
    inline void set_cookie(const std::string& cookie){
      COOKIE = cookie;
    }//change cookie
    
    std::unique_ptr<std::string> post(const std::string& url, const std::string& cookie, const std::string& post);
    
    inline ~Curl(){
      curl_easy_cleanup(handle);
    }//destructor
  };//wrapper class for Curl
}
#endif /* curl_hpp */