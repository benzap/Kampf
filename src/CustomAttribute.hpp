#ifndef CUSTOMATTRIBUTE__HPP
#define CUSTOMATTRIBUTE__HPP
//DESCRIPTION
/*
  Contains the CustomAttribute and CustomAttributePtr types
 */

//INCLUDES
#include <iostream>
#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//CLASSES
class CustomAttribute;

//DEFINITIONS

//MACROS

//TYPEDEFS

//ENUMS
//types that can be stored within the customAttributeValueMap
// they refer to integerType, floatType, and charType
#undef VOID
enum class enumAttribute {
  INTEGER,
  FLOAT,
  CHAR,
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
  stringType* s;
  void* v;
};

//FUNCTIONS

//BEGIN
class CustomAttribute {
private:
  enumAttribute valueType;
  CustomAttributeUnion value;
public:
  CustomAttribute() : valueType(enumAttribute::VOID) {
    value.v = nullptr;
  };
  CustomAttribute(integerType iValue);
  CustomAttribute(floatType fValue);
  CustomAttribute(charType cValue);
  CustomAttribute(intArrayType*);
  CustomAttribute(floatArrayType*);
  CustomAttribute(stringType*);
  CustomAttribute(void*);
  virtual ~CustomAttribute();

  integerType get_int();
  void set(integerType iValue);

  floatType get_float();
  void set(floatType fValue);

  charType get_char();
  void set(charType cValue);

  intArrayType* get_intArray();
  void set(intArrayType*);

  floatArrayType* get_floatArray();
  void set(floatArrayType*);

  stringType* get_string();
  void set(stringType*);

  void* get_void();
  void set(void*);

  enumAttribute getType();
};

#endif //END CUSTOMATTRIBUTE__HPP
