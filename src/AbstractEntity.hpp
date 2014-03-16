#ifndef ABSTRACTENTITY__HPP
#define ABSTRACTENTITY__HPP
//DESCRIPTION
/*!
  @file AbstractEntity.hpp
  @brief Abstract for all entities

  Entities are what represent particular pieces in a scene. They are
  used to handle anything that would appear on the screen. From
  sprites, to 3d models, to collision bounds.

  The AbstractEntity includes all of the same functionality as
  MainEntity, and serves as a barebones entity.
*/

//CLASSES
class AbstractEntity;

//DEFINITIONS

//! provided within the id field of an entity, will generate an ID
#define GENERATE_ID 0

//! abstract type symbol
#define ENTITY_ABSTRACT_TYPE "ABSTRACT"

//INCLUDES
#include <iostream>
#include <memory>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "Components.hpp"

//MACROS

//TYPEDEFS

//! Container used for storing components within the entity
typedef std::vector<AbstractComponent*> componentListType;

//! Container used for retrieving partial lists of components from the
//! entity.
typedef std::list<AbstractComponent*> partialComponentListType;
//FUNCTIONS

//BEGIN
class AbstractEntity {
private:
    //! Name of the entity
    stringType name;

    //! String representing the type of entity (not unique)
    stringType type;

    //! unique id describing the entity
    incrementType id;

    //! Container holding the components
    componentListType componentList;
public:

    //! Static variable holding the current available, unique,
    //! increment value
    static incrementType EntityIncrement;

    //! Constructor for abstract entity
    /*!
      
      @param name The name of the entity 
      @param id The id of the entity, this is usually automatically
      generated.
      @param type The type of the entity
     */
    AbstractEntity(stringType name,
		   incrementType id = GENERATE_ID,
		   stringType type = ENTITY_ABSTRACT_TYPE);
    virtual ~AbstractEntity();

    //! get the current name of the entity
    const stringType& getName();

    //! set the current name of the entity
    void setName(stringType name);

    //! get the type of the entity
    stringType getType();

    //! get the unique ID of the entity
    incrementType getID();

    //! returns the component container of the entity
    const componentListType& getComponentContainer();

    //! returns the list of components that are part of the given family
    partialComponentListType getComponentsByFamily(enumComponentFamily family);
    //! returns a list of components that have the same name
    partialComponentListType getComponentsByName(stringType name);

    //! adds the given component to the entity
    void addComponent(AbstractComponent* theComponent);
  

};


#endif //END ABSTRACTENTITY__HPP
