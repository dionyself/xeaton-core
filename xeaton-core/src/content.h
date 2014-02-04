/*
 * content.h
 *
 *  Created on: Feb 2, 2014
 *      Author: dionys
 */

#ifndef CONTENT_H_
#define CONTENT_H_





#endif /* CONTENT_H_ */

#include <cppcms/view.h>
#include <string>

namespace content  {
  struct message : public cppcms::base_content {
    std::string text;
  };
}
