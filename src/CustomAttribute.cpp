#include "CustomAttribute.hpp"

CustomAttribute::CustomAttribute(boolType bValue) : 
    valueType(enumAttribute::BOOLEAN) {
    value.b = bValue;
}

CustomAttribute::CustomAttribute(integerType iValue) :
    valueType(enumAttribute::INTEGER) {
    value.i = iValue;
}

CustomAttribute::CustomAttribute(floatType fValue) :
    valueType(enumAttribute::FLOAT) {
    value.f = fValue;
}

CustomAttribute::CustomAttribute(charType cValue) :
    valueType(enumAttribute::CHAR) {
    value.c = cValue;
}

CustomAttribute::CustomAttribute(intArrayType iaValue) :
    valueType(enumAttribute::INTEGER_VECTOR) {
    intArrayType* is = new intArrayType(iaValue);
    value.is = is;
}

CustomAttribute::CustomAttribute(floatArrayType faValue) :
    valueType(enumAttribute::FLOAT_VECTOR) {
    floatArrayType* fs = new floatArrayType(faValue);
    value.fs = fs;
}

CustomAttribute::CustomAttribute(stringType sValue) :
    valueType(enumAttribute::STRING) {
    stringType* s = new stringType(sValue);
    value.s = s;
}

CustomAttribute::CustomAttribute(void* vValue) :
    valueType(enumAttribute::VOID) {
    value.v = vValue;
}

CustomAttribute::CustomAttribute(Vector3 vecValue) :
    valueType(enumAttribute::VECTOR3) {
    Vector3* vs = new Vector3(vecValue);
    value.vs = vs;
}

CustomAttribute::~CustomAttribute() {
    this->freeResource();
}

void CustomAttribute::freeResource() {
    //TODO: dereference strings, int arrays, float arrays, voids
    if (valueType == enumAttribute::INTEGER_VECTOR) {
	delete value.is;
    }
    else if (valueType == enumAttribute::FLOAT_VECTOR) {
	delete value.fs;
    }
    else if (valueType == enumAttribute::STRING) {
	delete value.s;
    }
    else if (valueType == enumAttribute::VECTOR3) {
	delete value.vs;
    }
    else if (valueType == enumAttribute::VOID) {
	delete value.v;
    }
}

boolType CustomAttribute::get_bool() {
    return value.b;
}

void CustomAttribute::set(boolType bValue) {
    valueType = enumAttribute::BOOLEAN;
    value.b = bValue;
}

integerType CustomAttribute::get_int() {
    return value.i;
}

void CustomAttribute::set(integerType iValue) {
    valueType = enumAttribute::INTEGER;
    value.i = iValue;
}


floatType CustomAttribute::get_float() {
    return value.f;
}

void CustomAttribute::set(floatType fValue) {
    valueType = enumAttribute::FLOAT;
    value.f = fValue;
}

charType CustomAttribute::get_char() {
    return value.c;
}

void CustomAttribute::set(charType cValue) {
    valueType = enumAttribute::CHAR;
    value.c = cValue;
}

const intArrayType& CustomAttribute::get_intArray() {
    return *value.is;
}

void CustomAttribute::set(intArrayType iaValue) {
    valueType = enumAttribute::INTEGER_VECTOR;
    intArrayType* is = new intArrayType(iaValue);
    value.is = is;
}

const floatArrayType& CustomAttribute::get_floatArray() {
    return *value.fs;
}

void CustomAttribute::set(floatArrayType faValue) {
    valueType = enumAttribute::FLOAT_VECTOR;
    floatArrayType* fs = new floatArrayType(faValue);
    value.fs = fs;
}


const stringType& CustomAttribute::get_string() {
    return *value.s;
}

void CustomAttribute::set(stringType sValue) {
    valueType = enumAttribute::STRING;
    stringType* s = new stringType(sValue);
    value.s = s;
}


void* CustomAttribute::get_void() {
    return value.v;
}

void CustomAttribute::set(void* vValue) {
    valueType = enumAttribute::VOID;
    value.v = vValue;
}

const Vector3& CustomAttribute::get_vector() {
    return *value.vs;
}

void CustomAttribute::set(Vector3 vsValue) {
    valueType = enumAttribute::VECTOR3;
    Vector3* vs = new Vector3(vsValue);
    value.vs = vs;
}

enumAttribute CustomAttribute::getType() {
    return valueType;
}
