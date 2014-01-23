//============================================================================
// Name        : xeaton-core.cpp
// Author      : Dionys Rosario
// Version     :
// Copyright   : all rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>

class site : public cppcms::application {
 public:
  site(cppcms::service &srv) :
    cppcms::application(srv) {}
  virtual void main(std::string url);
};

void site::main(std::string /*url*/) {
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
      cppcms::applications_factory<site>());
    srv.run();
  }
  catch(std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
}
