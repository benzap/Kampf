#ifndef DATA_HPP_
#define DATA_HPP_
/* INCLUDES */
#include <iostream>
#include "kampf_general.hpp"
#include "Object.hpp"

/* CLASSES */
template <class T>
class Data;

/* TYPEDEF */



/* START */
template <class T>
class Data: public Object {
private:
  T dataStorage;
  bool bIsArray;
  unsigned int count;

public:

  Data();
  Data(T = NULL, unsigned int = 1, bool = false);

  ~Data();

  void printStatus();
  
  CALLBACK execute();

  CALLBACK setData(T);
  const T getData();
  CALLBACK deleteData();

  bool isArray();

  unsigned int getCount();
  CALLBACK setCount(unsigned int);
};


#endif //DATA_HPP_
