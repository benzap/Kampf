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
 
bool AbstractComponent::isActive() {
  return this->bActive;
}

void AbstractComponent::setActive() {
  this->bActive = true;
}

void AbstractComponent::setInactive() {
  this->bActive = false;
}


//value types

boolType AbstractComponent::getCustomAttribute_bool(stringType keyname) {
    assert(this->hasCustomAttribute(keyname));
    return this->customAttributeMap[keyname].get_bool();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, boolType bValue) {
    if (this->hasCustomAttribute(keyname)) {
	customAttributeMap[keyname].set(bValue);
    }
    else {
	auto customAttribute = CustomAttribute(bValue);
	customAttributeMap[keyname] = customAttribute;
    }
    return keyname;
}

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
const intArrayType& AbstractComponent::getCustomAttribute_intArray(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  return customAttributeMap[keyname].get_intArray();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, intArrayType iaValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(iaValue);
  }
  else {
    auto customAttribute = CustomAttribute(iaValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}

const floatArrayType& AbstractComponent::getCustomAttribute_floatArray(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_floatArray();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, floatArrayType faValue) {
  if (this->hasCustomAttribute(keyname)) {
    customAttributeMap[keyname].set(faValue);
  }
  else {
    auto customAttribute = CustomAttribute(faValue);
    customAttributeMap[keyname] = customAttribute;
  }
  return keyname;
}

const stringType& AbstractComponent::getCustomAttribute_string(stringType keyname) {
  assert(this->hasCustomAttribute(keyname));
  //TODO: check type
  return customAttributeMap[keyname].get_string();
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

const Vector3& AbstractComponent::getCustomAttribute_vector(stringType keyname) {
    assert(this->hasCustomAttribute(keyname));
    return customAttributeMap[keyname].get_vector();
}

stringType AbstractComponent::setCustomAttribute(stringType keyname, Vector3 vsValue) {
    if (this->hasCustomAttribute(keyname)) {
	customAttributeMap[keyname].set(vsValue);
    }
    else {
	auto customAttribute = CustomAttribute(vsValue);
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

void AbstractComponent::addChild(AbstractComponent* component) {
  this->children.push_back(component);
}

AbstractComponent* 
AbstractComponent::createChild(stringType name) {
  auto component = new AbstractComponent(name, enumComponentFamily::ABSTRACT, false);
  
  this->children.push_back(component);
  return component;
}

bool AbstractComponent::hasChildren() {
  if (this->children.empty()) {
    return false;
  }
  return true;
}

CustomAttribute* AbstractComponent::get(stringType keyname) {
    return &(customAttributeMap[keyname]);
}

void AbstractComponent::set(stringType keyname, CustomAttribute attr) {
    customAttributeMap[keyname] = attr;
}

const componentContainerType* AbstractComponent::getChildContainer() {
  return &this->children;
}

AbstractComponent* createAbstractComponent(
    stringType name,
    boolType bIsParent) {
    auto abstractComponent = new AbstractComponent(
	name,
	enumComponentFamily::ABSTRACT,
	bIsParent);

    return abstractComponent;
}
