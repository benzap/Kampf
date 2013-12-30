#ifndef ABSTRACTENTITY__HPP
#define ABSTRACTENTITY__HPP
//DESCRIPTION
/*
  Entities are what represent particular pieces in a scene. Entities
  are described with components.
 */

//CLASSES
class AbstractEntity;

//DEFINITIONS

//provided within the id field of an entity, will generate an ID
#define GENERATE_ID 0
#define ENTITY_ABSTRACT_TYPE "ABSTRACT"

//INCLUDES
#include <iostream>
#include <memory>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "Components.hpp"

//MACROS

//TYPEDEFS
typedef std::vector<AbstractComponent*> componentListType;
typedef std::list<AbstractComponent*> partialComponentListType;
//FUNCTIONS

//BEGIN
class AbstractEntity {
private:
  stringType name;
  stringType type;
  incrementType id;
  componentListType componentList;
public:
  static incrementType EntityIncrement;

  AbstractEntity(stringType name,
		 incrementType id = GENERATE_ID,
		 stringType type = ENTITY_ABSTRACT_TYPE);
  virtual ~AbstractEntity();

  const stringType& getName();
  void setName(stringType name);
  stringType getType();
  incrementType getID();

  const componentListType& getComponentContainer();
  partialComponentListType getComponentsByFamily(enumComponentFamily family);
  partialComponentListType getComponentsByName(stringType name);
  
  void addComponent(AbstractComponent* theComponent);
  

};


#endif //END ABSTRACTENTITY__HPP
