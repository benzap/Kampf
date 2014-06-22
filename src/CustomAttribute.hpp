#ifndef CUSTOMATTRIBUTE__HPP
#define CUSTOMATTRIBUTE__HPP
//DESCRIPTION
/*
  Contains the CustomAttribute and CustomAttributePtr types
*/

//CLASSES
class CustomAttribute;

//INCLUDES
#include <iostream>
#include "KF_globals.hpp"
#include "KF_utilities.hpp"

#include "KF_Vector3.hpp"
//DEFINITIONS

//MACROS

//TYPEDEFS

//ENUMS
//types that can be stored within the customAttributeValueMap
// they refer to integerType, floatType, and charType
#undef VOID
enum class enumAttribute {
    BOOLEAN,
	INTEGER,
	FLOAT,
	CHAR,
	VOID,
	INTEGER_VECTOR,
	FLOAT_VECTOR,
	STRING,
	VECTOR3
	};

//UNIONS
union CustomAttributeUnion {
    boolType b;
    integerType i;
    floatType f;
    charType c;
    stringType* s;
    void* v;
    intArrayType* is;
    floatArrayType* fs;
    Vector3* vs;
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
    CustomAttribute(boolType bValue);
    CustomAttribute(integerType iValue);
    CustomAttribute(floatType fValue);
    CustomAttribute(charType cValue);
    CustomAttribute(intArrayType);
    CustomAttribute(floatArrayType);
    CustomAttribute(stringType);
    CustomAttribute(void*);
    CustomAttribute(Vector3);
    virtual ~CustomAttribute();

    void freeResource();

    boolType get_bool();
    void set(boolType bValue);

    integerType get_int();
    void set(integerType iValue);

    floatType get_float();
    void set(floatType fValue);

    charType get_char();
    void set(charType cValue);

    const intArrayType& get_intArray();
    void set(intArrayType);

    const floatArrayType& get_floatArray();
    void set(floatArrayType);

    const stringType& get_string();
    void set(stringType);

    const Vector3& get_vector();
    void set(Vector3);

    void* get_void();
    void set(void*);

    enumAttribute getType();
};

#endif //END CUSTOMATTRIBUTE__HPP
