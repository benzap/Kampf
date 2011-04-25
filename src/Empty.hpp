#ifndef EMPTY_HPP_
#define EMPTY_HPP_
/* INCLUDES */
#include <iostream>
#include "kampf_general.hpp"
#include "Object.hpp"

/* CLASSES */

class Empty;

/* TYPEDEF */






/* START */

class Empty: public Object {
public:

  Empty(); 
  ~Empty();

  void printStatus();
  
  CALLBACK execute();

};


#endif //EMPTY_HPP_
