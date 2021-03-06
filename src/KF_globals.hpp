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
#include <cassert>
#include <cfloat>
#include <map>

//CLASSES

//DEFINITIONS
//to fix some issues concerning windows
#if defined(KF_WIN)
#undef VOID
#undef void
#undef INTEGER
#undef int
#undef FLOAT
#undef float
#undef VECTOR
#undef vector
#endif

#define KF_MAX_FLOAT FLT_MAX

//MACROS

//TYPEDEFS
//incrementer type to use
typedef int incrementType;

//string type to use
typedef std::string stringType;

//integer type to use
typedef int integerType;

//GUID type for unique identification
typedef std::string guidType;

//timer value duration to use
typedef unsigned int timeType;

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

#include "CustomAttribute.hpp"

//custom attribute map type
typedef std::map<stringType, CustomAttribute> customMapType;


//FUNCTIONS

//ENUMS
enum class enumInitType {
    Server,
	Basic,
	Manual
	};

enum class enumWindowType {
    SERVER,
	SDL,
	SFML
	};

enum class enumRenderType {
    SERVER,
	SDL,
	OPENGL,
	DIRECTX
	};


#endif //END KF_GLOBALS__HPP
