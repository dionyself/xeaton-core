//============================================================================
// Name        : xeaton-core.cpp
// Author      : Dionys Rosario
// Version     :
// Copyright   : author rights reserved
// Description : xeaton-core part of Xeaton Gaming platform
//============================================================================

#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/applications_pool.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "content.h"
using namespace std;

class UserSite : public cppcms::application {
 public:
  UserSite();
};

class MainSite : public cppcms::application {
 public:
  MainSite(cppcms::service &srv) :
    cppcms::application(srv) {
	  dispatcher().assign("/number/(\\d+)",&MainSite::number,this,1);
	  mapper().assign("number","/number/{1}");
	  dispatcher().assign("/smile",&MainSite::smile,this);
	  mapper().assign("smile","/smile");
	  dispatcher().assign("",&MainSite::welcome,this);
	  mapper().assign("");
	  mapper().root("/home");
	  dispatcher().assign("/static/([a-z_0-9\.]+\.txt)",&MainSite::serve_file,this,1);
  }

  void serve_file(std::string file_name) {
    std::ifstream f(("some_dir_name/" + file_name).c_str());
    if(!f) {
      response().status(404);
    }
    else {
      response().content_type("application/octet-stream");
      response().out() << f.rdbuf();
    }
  }

  void number(std::string num) {
    int no = atoi(num.c_str());
    response().out() << "The number is " << no << "<br/>\n";
    response().out() << "<a href='" << url("/") << "'>Go back</a>";
  }

  void smile() {
	    content::message c;
	    c.text=">>>Hello<<<";
	    render("message",c);
  }

  void welcome() {
      response().out() <<
          "<h1> Welcome To Page with links </h1>\n"
          "<a href='" << url("/number",1)  << "'>1</a><br>\n"
          "<a href='" << url("/number",15) << "'>15</a><br>\n"
          "<a href='" << url("/smile") << "' >:-)</a><br>\n";
  }
};

int main(int argc, char ** argv) {
  try {
    cppcms::service srv(argc, argv);
    srv.applications_pool().mount(
      cppcms::applications_factory<MainSite>());
    std::cout << "starting http main service..." << std::endl;
    srv.run();
  }
  catch(std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
}
