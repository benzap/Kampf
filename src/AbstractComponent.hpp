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
#include<memory>

#include "KF_globals.hpp"
#include "CustomAttribute.hpp"

//CLASSES
class AbstractComponent;

//DEFINITIONS

//MACROS

//TYPEDEFS

//type used by abstract component to store custom attributes
typedef std::map<stringType, CustomAttribute> customAttributeMapType;

//used for the components to store components as references without
//requiring dereferencing on deletion

//componentContainer type
typedef std::list<std::shared_ptr<AbstractComponent> > componentContainerType;

//ENUMS The main component family enumeration. This describes what the
//component is, for dynamic casting.
enum enumComponentFamily {
    ABSTRACT,
    COLLISION,
    PHYSICS,
    GRAPHICS,
    CUSTOM
};

//FUNCTIONS
std::shared_ptr<AbstractComponent> createAbstractComponent(
    stringType name, boolType bIsParent = true);

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

    //a boolean which determines whether the given component is
    //considered active or inactive
    bool bActive = true;


    //holds custom attribute values
    customAttributeMapType customAttributeMap;

    //the children of the component. typically the children should be
    //the same type as its parent.
    componentContainerType children;
public:
    //set to true if the component is active
    bool bEnabled = true;
    
    AbstractComponent(
	stringType name, 
	enumComponentFamily family = enumComponentFamily::ABSTRACT,
	bool bIsParent = true);

    virtual ~AbstractComponent();
  
    const stringType& getName();
    void setName(stringType);
  
    enumComponentFamily getFamily();
  
    bool isParent();
  
    bool isActive();
    void setActive();
    void setInactive();

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
 
    CustomAttribute* get(stringType);
    void set(stringType, CustomAttribute);

    //creates a new child, and pushes the child component into the
    //child container. Each inherited type creates and pushes to the
    //container the same type of component as itself.
    virtual std::shared_ptr<AbstractComponent> createChild(
	stringType name);
    
    //deleting children can be done through the list itself
    void addChild(std::shared_ptr<AbstractComponent>);
    bool hasChildren();
    const componentContainerType* getChildContainer();

};

#endif //END ABSTRACTCOMPONENT__HPP
