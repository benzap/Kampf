#ifndef KF_GLOBALS__HPP
#define KF_GLOBALS__HPP
//DESCRIPTION
/*
  This file contains a bunch of global values used between all of the
  classes within kampf
 */

//INCLUDES
#include <string>
#include <vector>

//CLASSES

//DEFINITIONS
//to fix some issues concerning windows
#if defined(KF_WIN)
#undef VOID
#undef INTEGER
#undef FLOAT
#undef VECTOR
#endif


//MACROS

//TYPEDEFS
//incrementer type to use
typedef int incrementType;

//string type to use
typedef std::string stringType;

//integer type to use
typedef int integerType;

//floating point type to use
typedef double floatType;

//character type to use
typedef char charType;


//boolean type to use
typedef bool boolType;

//int array type
typedef std::vector<integerType> intArrayType;

//float array type
typedef std::vector<floatType> floatArrayType;

//FUNCTIONS

//BEGIN


#endif //END KF_GLOBALS__HPP
