#include "CustomAttribute.hpp"

CustomAttributeValue::CustomAttributeValue(integerType iValue) :
  valueType(enumAttributeValue::INTEGER) {
  this->value.i = iValue;
}

CustomAttributeValue::CustomAttributeValue(floatType fValue) :
  valueType(enumAttributeValue::FLOAT) {
  this->value.f = fValue;
}

CustomAttributeValue::CustomAttributeValue(charType cValue) :
  valueType(enumAttributeValue::CHAR) {
  this->value.c = cValue;
}

CustomAttributeValue::~CustomAttributeValue() {

}

integerType CustomAttributeValue::getValue_int() {
  //TODO: check if it is an int
  return this->value.i;
}
floatType CustomAttributeValue::getValue_float() {
  //TODO: check if it is a float
  return this->value.f;
}
charType CustomAttributeValue::getValue_char() {
  //TODO: check if it is a char
  return this->value.c;
}

void CustomAttributeValue::setValue(integerType iValue) {
  this->valueType = enumAttributeValue::INTEGER;
  this->value.i = iValue;
}

void CustomAttributeValue::setValue(floatType fValue) {
  this->valueType = enumAttributeValue::FLOAT;
  this->value.f = fValue;
}

void CustomAttributeValue::setValue(charType cValue) {
  this->valueType = enumAttributeValue::CHAR;
  this->value.c = cValue;
}

CustomAttributePtr::CustomAttributePtr(intArrayType* iArray) :
  ptrType(enumAttributePtr::INTEGER_VECTOR) {
  this->ptr = static_cast<void*>(iArray);
}

CustomAttributePtr::CustomAttributePtr(floatArrayType* fArray) :
  ptrType(enumAttributePtr::FLOAT_VECTOR) {
  this->ptr = static_cast<void*>(fArray);
}

CustomAttributePtr::CustomAttributePtr(stringType* cArray) :
  ptrType(enumAttributePtr::STRING) {
  this->ptr = static_cast<void*>(cArray);
}

CustomAttributePtr::CustomAttributePtr(void* ptr) :
  ptrType(enumAttributePtr::VOID) {
  this->ptr = ptr;
}

CustomAttributePtr::~CustomAttributePtr() {

}

intArrayType* CustomAttributePtr::getPtr_intArray() {
  //TODO: check if it is an int array
  return static_cast<intArrayType*>(this->ptr);
}

floatArrayType* CustomAttributePtr::getPtr_floatArray() {
  //TODO: check if it is an float array
  return static_cast<floatArrayType*>(this->ptr);
}

stringType* CustomAttributePtr::getPtr_string() {
  //TODO: check if it is an string
  return static_cast<stringType*>(this->ptr);
}

void* CustomAttributePtr:: getVoidPtr() {
  return this->ptr;
}

void CustomAttributePtr::setPtr(intArrayType* iArray) {
  this->ptrType = enumAttributePtr::INTEGER_VECTOR;
  this->ptr = static_cast<void*>(iArray);
}

void CustomAttributePtr::setPtr(floatArrayType* fArray) {
  this->ptrType = enumAttributePtr::FLOAT_VECTOR;
  this->ptr = static_cast<void*>(fArray);
}

void CustomAttributePtr::setPtr(stringType* cArray) {
  this->ptrType = enumAttributePtr::STRING;
  this->ptr = static_cast<void*>(cArray);
}

void CustomAttributePtr::setPtr(void* ptr) {
  this->ptrType = enumAttributePtr::VOID;
  this->ptr = ptr;
}
