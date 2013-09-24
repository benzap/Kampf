#ifndef ABSTRACTCOMPONENT__HPP
#define ABSTRACTCOMPONENT__HPP
//DESCRIPTION
/*
  The abstract component makes up all of the components contained
  within the system.
 */

//INCLUDES
#include<iostream>
#include<map>
#include<string>
#include<list>

#include "KF_globals.hpp"
#include "CustomAttribute.hpp"

//CLASSES
class AbstractComponent;

//DEFINITIONS

//MACROS

//TYPEDEFS

//type used by abstract component to store custom attributes
typedef std::map<stringType, CustomAttribute> customAttributeMapType;

//ENUMS The main component family enumeration. This describes what the
//component is, for dynamic casting.
enum enumComponentFamily {
  ABSTRACT,
  COLLISION,
  PHYSICS,
  CUSTOM
};

//FUNCTIONS

//BEGIN
class AbstractComponent {
private:
  //the name of our component. does not need to be unique
  stringType name;

  //the family in which the component belongs
  enumComponentFamily family;

  //a boolean which determines if the component is the parent, or is a
  //child
  bool bIsParent;

  //holds custom attribute values
  customAttributeMapType customAttributeMap;

  //the children of the component. typically the children should be
  //the same type as its parent.
  std::list<AbstractComponent> children;
public:
  AbstractComponent(stringType name, 
		    enumComponentFamily family = enumComponentFamily::ABSTRACT,
		    bool bIsParent = true);
  virtual ~AbstractComponent();
  
  const stringType& getName();
  void setName(stringType);
  
  enumComponentFamily getFamily();
  
  bool isParent();
  
  //value types
  integerType getCustomAttribute_int(stringType);
  stringType setCustomAttribute(stringType, integerType);

  floatType getCustomAttribute_float(stringType);
  stringType setCustomAttribute(stringType, floatType);

  charType getCustomAttribute_char(stringType);
  stringType setCustomAttribute(stringType, charType);


  //ptr types
  intArrayType* getCustomAttribute_intArray(stringType);
  stringType setCustomAttribute(stringType, intArrayType*);
  floatArrayType* getCustomAttribute_floatArray(stringType);
  stringType setCustomAttribute(stringType, floatArrayType*);
  stringType& getCustomAttribute_string(stringType);
  stringType setCustomAttribute(stringType, stringType);
  void* getCustomAttribute_void(stringType);
  stringType setCustomAttribute(stringType, void*);
  
  bool hasCustomAttribute(stringType);
  enumAttribute getCustomAttributeType(stringType);
  void deleteCustomAttribute(stringType);

};

#endif //END ABSTRACTCOMPONENT__HPP