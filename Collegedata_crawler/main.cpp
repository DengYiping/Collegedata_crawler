//
//  main.cpp
//  Collegedata_crawler
//
//  Created by Scott Deng on 12/21/15.
//  Copyright © 2015 Scott Deng. All rights reserved.
//

#include <iostream>
#include <boost/regex.hpp>
#include "curl.hpp"
int main(int argc, const char * argv[]) {
  curl::init();
  curl::Curl baidu("www.google.com");
  auto buffer = baidu.get();
  std::cout<<*buffer<<std::endl;
  curl::cleanup();
}
