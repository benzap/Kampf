#ifndef CUSTOMATTRIBUTE__HPP
#define CUSTOMATTRIBUTE__HPP
//DESCRIPTION
/*
  Contains the CustomAttributeValue and CustomAttributePtr types
 */

//INCLUDES
#include <iostream>
#include "KF_globals.hpp"

//CLASSES
class CustomAttributeValue;
class CustomAttributePtr;

//DEFINITIONS

//MACROS

//TYPEDEFS

//ENUMS
//types that can be stored within the customAttributeValueMap
// they refer to integerType, floatType, and charType
enum enumAttributeValue {
  INTEGER,
  FLOAT,
  CHAR
};

//types that can be stored within the customAttributePtrMap
// they refer to void*, intArrayType, floatArrayType, stringType
enum enumAttributePtr {
  VOID,
  INTEGER_VECTOR,
  FLOAT_VECTOR,
  STRING
};

//UNIONS
union CustomAttributeUnion {
  integerType i;
  floatType f;
  charType c;
};

//FUNCTIONS

//BEGIN
class CustomAttributeValue {
private:
  enumAttributeValue valueType;
  CustomAttributeUnion value;
public:
  CustomAttributeValue(integerType iValue);
  CustomAttributeValue(floatType fValue);
  CustomAttributeValue(charType cValue);
  virtual ~CustomAttributeValue();

  integerType getValue_int();
  floatType getValue_float();
  charType getValue_char();
  void setValue(integerType iValue);
  void setValue(floatType fValue);
  void setValue(charType cValue);
};

class CustomAttributePtr {
private:
  enumAttributePtr ptrType;
  void* ptr;
public:
  CustomAttributePtr(intArrayType*);
  CustomAttributePtr(floatArrayType*);
  CustomAttributePtr(stringType*);
  CustomAttributePtr(void*);
  virtual ~CustomAttributePtr();
  
  intArrayType* getPtr_intArray();
  floatArrayType* getPtr_floatArray();
  stringType* getPtr_string();
  void* getVoidPtr();
  void setPtr(intArrayType*);
  void setPtr(floatArrayType*);
  void setPtr(stringType*);
  void setPtr(void*);
};

#endif //END CUSTOMATTRIBUTE__HPP
