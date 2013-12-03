#include "CustomAttribute.hpp"

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

CustomAttribute::CustomAttribute(intArrayType* iaValue) :
  valueType(enumAttribute::INTEGER_VECTOR) {
  value.v = static_cast<void*>(iaValue);
}

CustomAttribute::CustomAttribute(floatArrayType* faValue) :
  valueType(enumAttribute::FLOAT_VECTOR) {
  value.v = static_cast<void*>(faValue);
}

CustomAttribute::CustomAttribute(stringType* sValue) :
  valueType(enumAttribute::STRING) {
  value.s = sValue;
}

CustomAttribute::CustomAttribute(void* vValue) :
  valueType(enumAttribute::VOID) {
  value.v = vValue;
}

CustomAttribute::~CustomAttribute() {
  //TODO: dereference strings, int arrays, float arrays, voids
}


integerType CustomAttribute::get_int() {
  //TODO: check if it exists
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

intArrayType* CustomAttribute::get_intArray() {
  return static_cast<intArrayType*>(value.v);
}

void CustomAttribute::set(intArrayType* iaValue) {
  valueType = enumAttribute::INTEGER_VECTOR;
  value.v = static_cast<void*>(iaValue);
}


floatArrayType* CustomAttribute::get_floatArray() {
  return static_cast<floatArrayType*>(value.v);
}

void CustomAttribute::set(floatArrayType* faValue) {
  valueType = enumAttribute::FLOAT_VECTOR;
  value.v = static_cast<void*>(faValue);
}


stringType* CustomAttribute::get_string() {
  return value.s;
}

void CustomAttribute::set(stringType* sValue) {
  valueType = enumAttribute::STRING;
  value.s = sValue;
}


void* CustomAttribute::get_void() {
  return value.v;
}

void CustomAttribute::set(void* vValue) {
  valueType = enumAttribute::VOID;
  value.v = vValue;
}


enumAttribute CustomAttribute::getType() {
  return valueType;
}
