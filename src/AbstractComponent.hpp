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
typedef std::map<incrementType, CustomAttributeValue> customAttributeValueMap;
//type used by abstract component to store custom ptr attributes
typedef std::map<incrementType, CustomAttributePtr> customAttributePtrMap;

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
  //the increment used to describe new custom attributes
  incrementType				CustomValueID;
  
  //the increment used to describe new custom referenced values
  incrementType				CustomPtrID;
  
  //the name of our component. does not need to be unique
  stringType name;

  //the family in which the component belongs
  enumComponentFamily				family;

  //a boolean which determines if the component is the parent, or is a
  //child
  bool						bIsParent;

  //holds custom attribute values
  std::map<incrementType, CustomAttributeValue> customValueMap;

  //holds custom attribute references to values. useful for arrays, and objects
  std::map<incrementType, CustomAttributePtr>	customPtrMap;

  //the children of the component. typically the children should be
  //the same type as its parent.
  std::list<AbstractComponent>			children;
public:
  AbstractComponent(stringType name, 
		    enumComponentFamily family = enumComponentFamily::ABSTRACT,
		    bool bIsParent = true);
  virtual ~AbstractComponent();
  
  const stringType& getName();
  void setName(stringType&);
  
  enumComponentFamily getFamily();
  
  bool isParent();
  
  auto getCustomAttributeValue(incrementType);
  incrementType setCustomAttributeValue(integerType);
  incrementType setCustomAttributeValue(floatType);
  incrementType setCustomAttributeValue(charType);
  enumAttributeValue getCustomAttributeValueType(incrementType);

  void* getCustomAttributePtr(incrementType);
  incrementType setCustomAttributePtr(void*, enumAttributePtr);
  enumAttributePtr getCustomAttributePtrType(incrementType);

};

#endif //END ABSTRACTCOMPONENT__HPP
