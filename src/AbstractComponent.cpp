#include "AbstractComponent.hpp"

#include <iostream>
#include <cassert>

AbstractComponent::AbstractComponent(stringType name, enumComponentFamily family, bool bIsParent) :
  name(name),
  family(family),
  bIsParent(bIsParent) {

}

AbstractComponent::~AbstractComponent() {

}
  
const stringType& AbstractComponent::getName() {
  return this->name;
}

void AbstractComponent::setName(stringType name) {
  this->name = name;
}
  
enumComponentFamily AbstractComponent::getFamily() {
  return this->family;
}
  
bool AbstractComponent::isParent() {
  return this->bIsParent;
}
 
//value types
integerType AbstractComponent::getCustomAttribute_int(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return this->customAttributeMap[keyname].get_int();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, integerType iValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(iValue);
  }
  else {
    auto customAttribute = CustomAttribute(iValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}


floatType AbstractComponent::getCustomAttribute_float(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_float();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, floatType fValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(fValue);
  }
  else {
    auto customAttribute = CustomAttribute(fValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}


charType AbstractComponent::getCustomAttribute_char(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_char();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, charType cValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(cValue);
  }
  else {
    auto customAttribute = CustomAttribute(cValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}



//ptr types
intArrayType* AbstractComponent::getCustomAttribute_intArray(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_intArray();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, intArrayType* iaValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(iaValue);
  }
  else {
    auto customAttribute = CustomAttribute(iaValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}

floatArrayType* AbstractComponent::getCustomAttribute_floatArray(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_floatArray();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, floatArrayType* faValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(faValue);
  }
  else {
    auto customAttribute = CustomAttribute(faValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}

stringType& AbstractComponent::getCustomAttribute_string(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return *customAttributeMap[keyname].get_string();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, stringType sValue) {
  auto sValuePtr = new stringType(sValue);
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(sValuePtr);
  }
  else {
    auto customAttribute = CustomAttribute(sValuePtr);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}

void* AbstractComponent::getCustomAttribute_void(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_void();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, void* vValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(vValue);
  }
  else {
    auto customAttribute = CustomAttribute(vValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}

  
bool AbstractComponent::hasCustomAttribute(stringType keyname) {
  if (this->customAttributeMap.find(keyname) == this->customAttributeMap.end()) {
    return false;
  }
  return true;
}

enumAttribute AbstractComponent::getCustomAttributeType(stringType keyname) {
  return customAttributeMap[keyname].getType();
}

void AbstractComponent::deleteCustomAttribute(stringType keyname) {
  if(this->hasCustomAttribute(keyname)) {
    auto iterAttribute = this->customAttributeMap.find(keyname);
    this->customAttributeMap.erase(iterAttribute);
  }
}

void AbstractComponent::addChild(std::shared_ptr<AbstractComponent> component) {
  this->children.push_back(component);
}

std::shared_ptr<AbstractComponent> 
AbstractComponent::createChild(stringType name, 
			       enumComponentFamily family) {
  auto component = std::shared_ptr<AbstractComponent>
    (new AbstractComponent(name, family, false));
  
  this->children.push_back(component);
  return component;
}

bool AbstractComponent::hasChildren() {
  if (this->children.empty()) {
    return false;
  }
  return true;
}

componentContainerType* AbstractComponent::getChildContainer() {
  return this->children;
}
