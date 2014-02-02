//============================================================================
// Name        : xeaton-core.cpp
// Author      : Dionys Rosario
// Version     :
// Copyright   : author rights reserved
// Description : xeaton-core part of Xeaton Gaming platform
//============================================================================

#include <iostream>
using namespace std;
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/applications_pool.h>
#include <iostream>
#include <stdlib.h>

class UserSite : public cppcms::application {
 public:
  UserSite();
};

class MainSite : public cppcms::application {
 public:
  MainSite(cppcms::service &srv) :
    cppcms::application(srv) {}
  virtual void main(std::string url);
};

void MainSite::main(std::string /*url*/) {
  response().out() <<
    "<html>\n"
    "<body>\n"
    "  <h1>{'ans':'200 OK', 'POST-BACK':{},"
    "'session_hash':'af5daf5adf5d'}</h1>\n"
    "</body>\n"
    "</html>\n";
}

int main(int argc, char ** argv) {
  try {
    cppcms::service srv(argc, argv);
    srv.applications_pool().mount(
      cppcms::applications_factory<MainSite>());
    std::cout << "starting http service..." << std::endl;
    srv.run();
  }
  catch(std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
}
