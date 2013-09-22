#include "AbstractComponent.hpp"

#include <iostream>

AbstractComponent::AbstractComponent(stringType name, enumComponentFamily family, bool bIsParent) :
  CustomValueID(0),
  CustomPtrID(0),
  name(name),
  family(family),
  bIsParent(bIsParent) {
  
}

AbstractComponent::~AbstractComponent() {

}
  
const stringType& AbstractComponent::getName() {
  return this->name;
}

void AbstractComponent::setName(stringType& name) {
  this->name = name;
}
  
enumComponentFamily AbstractComponent::getFamily() {
  return this->family;
}
  
bool AbstractComponent::isParent() {
  return this->bIsParent;
}
  
auto AbstractComponent::getCustomAttributeValue(incrementType index) {
  return 0;
}

incrementType AbstractComponent::setCustomAttributeValue(integerType) {
  return 0;
}

incrementType AbstractComponent::setCustomAttributeValue(floatType) {
  return 0;
}

incrementType AbstractComponent::setCustomAttributeValue(charType) {
  return 0;
}

enumAttributeValue AbstractComponent::getCustomAttributeValueType(incrementType index) {
  return enumAttributeValue::INTEGER;
}

void* AbstractComponent::getCustomAttributePtr(incrementType index) {
  return nullptr;
}

incrementType AbstractComponent::setCustomAttributePtr(void* ptr, enumAttributePtr ptrType) {
  return 0;
}

enumAttributePtr AbstractComponent::getCustomAttributePtrType(incrementType index) {
  return enumAttributePtr::VOID;
}
