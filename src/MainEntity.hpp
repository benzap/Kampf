#ifndef MAINENTITY__HPP
#define MAINENTITY__HPP
//DESCRIPTION
/*
  This is the main entity class, which inherits everything from
  abstract entity, and nothing else
 */
//CLASSES
class MainEntity;

//INCLUDES
#include "AbstractEntity.hpp"

//DEFINITIONS

#define ENTITY_MAIN_TYPE "MAIN"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class MainEntity : public AbstractEntity {
private:
  
public:
  MainEntity(stringType name,
	     incrementType id = GENERATE_ID);
  virtual ~MainEntity();
};

#endif //END MAINENTITY__HPP
