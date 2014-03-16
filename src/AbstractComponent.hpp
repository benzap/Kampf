#ifndef ABSTRACTCOMPONENT__HPP
#define ABSTRACTCOMPONENT__HPP
//DESCRIPTION
/*!
  @file AbstractComponent.hpp
  @brief Abstract for all components

  The abstract component is used to describe each component within the
  system. This abstract includes all of the custom attribute
  functionality, which allows for more dynamic types to be included to
  describe a component.

  Components can also store children of itself, which means you can
  develop a hierarchy of the same component. How this hierarchy is
  built depends on the type of component.

  To summarize, components are containers that can fit into a tree
  hierarchy. These containers hold dynamic types through the
  CustomAttribute type.
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

//! type used by abstract component to store custom attributes
typedef std::map<stringType, CustomAttribute> customAttributeMapType;

//! componentContainer type
typedef std::list<AbstractComponent*> componentContainerType;

//ENUMS

/*! The main component family enumeration. This describes what the
  component is, for dynamic casting.
*/
enum enumComponentFamily {
    ABSTRACT,
    COLLISION,
    PHYSICS,
    GRAPHICS,
    CUSTOM
};

//FUNCTIONS

//! Allocates a new abstract component and returns a pointer to it
/*!
  @param name The name to give the component
  @param bIsParent Set to false if the component will reside as the 
  child of another component
 */
AbstractComponent* createAbstractComponent(
    stringType name, boolType bIsParent = true);

//BEGIN
class AbstractComponent {
private:
    //! the name of our component. does not need to be unique
    stringType name;

    //! the family in which the component belongs
    enumComponentFamily family;

    //! a boolean which determines if the component is the parent, or
    //is a child
    bool bIsParent;

    //! a boolean which determines whether the given component is
    //considered active or inactive
    bool bActive = true;


    //! holds custom attribute values
    customAttributeMapType customAttributeMap;

    //! the children of the component. typically the children should
    //be the same type as its parent.
    componentContainerType children;
public:
    //! set to true if the component is active
    bool bEnabled = true;

    /*!
      @param name the name to give to the component
      @param family the family type of the component.
      @param bIsParent set false, if the component resides
      as a child of another component.
     */
    AbstractComponent(
	stringType name, 
	enumComponentFamily family = enumComponentFamily::ABSTRACT,
	bool bIsParent = true);

    virtual ~AbstractComponent();

    //! get the name of the component
    const stringType& getName();

    //! set the name of the component
    void setName(stringType);

    //! get the family of the component
    enumComponentFamily getFamily();

    //! returns true if the component is the parent (top-level component)
    bool isParent();

    //! returns true if the component is active.
    /*!
      
      This variable is usually checked by the systems to determine if
      it should be processed.0
     */
    bool isActive();

    //! sets the current component active
    void setActive();

    //! sets the current component inactive (disables it)
    void setInactive();

    //value types

    //! grabs the integer value for the given component key
    integerType getCustomAttribute_int(stringType keyname);

    //! sets the integer value for the given component key
    stringType setCustomAttribute(stringType keyname, integerType iValue);

    //! grabs the float value for the given component key
    floatType getCustomAttribute_float(stringType keyname);

    //! sets the float value for the given component key
    stringType setCustomAttribute(stringType keyname, floatType fValue);

    //! grabs the character value for the given component key
    charType getCustomAttribute_char(stringType keyname);

    //! sets the character value for the given component key
    stringType setCustomAttribute(stringType keyname, charType cValue);

    //ptr types

    //! grabs the integer array for the given component key
    intArrayType* getCustomAttribute_intArray(stringType keyname);

    //! sets the integer array for the given component key
    stringType setCustomAttribute(stringType keyname,
				  intArrayType* iaValue);

    //! grabs the float array for the given component key
    floatArrayType* getCustomAttribute_floatArray(stringType keyname);

    //! sets the float array for the given component key
    stringType setCustomAttribute(stringType keyname,
				  floatArrayType* faValue);

    //! gets the string value for the given component key
    stringType& getCustomAttribute_string(stringType keyname);

    //! sets the string value for the given component key
    stringType setCustomAttribute(stringType keyname, stringType sValue);

    //! gets the void pointer for the given component key
    void* getCustomAttribute_void(stringType keyname);

    //! sets the void pointer for the given component key
    stringType setCustomAttribute(stringType keyname, void* vValue);

    //! returns true, if the given key exists within the component
    bool hasCustomAttribute(stringType keyname);

    //! returns the type of the given key stored in the component
    enumAttribute getCustomAttributeType(stringType keyname);

    //! deletes the component attribute with the given keyname
    void deleteCustomAttribute(stringType keyname);

    //! returns the CustomAttribute from the component with the given key
    CustomAttribute* get(stringType keyname);

    //! sets the CustomAttribute for the component with the given keyname
    void set(stringType keyname, CustomAttribute attr);

    //! creates a new child, and pushes the child component into the
    //! child container. Each inherited type creates and pushes to the
    //! container the same type of component as itself.
    virtual AbstractComponent* createChild(
	stringType name);
    
    //! adds the given component to the component
    void addChild(AbstractComponent* component);

    //! returns true if the component has children
    bool hasChildren();

    //! returns the container used to store the component's children
    const componentContainerType* getChildContainer();

};

#endif //END ABSTRACTCOMPONENT__HPP
