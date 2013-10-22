#ifndef KF_TEST__HPP
#define KF_TEST__HPP
//DESCRIPTION
/*
  This contains a bunch of utility functions to use within the tests
  to speed up test creation, and provide more useful output
 */

//INCLUDES
#include <iostream>
#include "kampf.hpp"

//CLASSES

//DEFINITIONS

//MACROS
#define KF_INIT_TEST(testnum, comment)				\
  std::cout << "Test No. " << testnum;				\
  std::cout << "\t - " << comment << "\t";			\
  testnum++;

#define TEST_NAME(filename)						\
  std::cout << std::endl;						\
  std::cout << "+++++++++++++++++ UNIT TEST +++++++++++" << std::endl;	\
  std::cout << "FILE:\t" << filename << std::endl;			\
  int __numtest = 1;

#define TEST_EQUAL(firstVal, secondVal, comment)			\
  KF_INIT_TEST(__numtest, comment);					\
  if ((firstVal) == (secondVal)) std::cout << "> PASSED" << std::endl;	\
  else std::cout << "X FAILED" << std::endl;				

#define TEST_BOOL(boolVal, comment)				\
  KF_INIT_TEST(__numtest, comment);				\
  if (boolVal) std::cout << "> PASSED" << std::endl;		\
  else std::cout << "X FAILED" << std::endl;				

//TYPEDEFS

//NAMESPACE


//FUNCTIONS

//BEGIN


#endif //END KF_TEST__HPP
