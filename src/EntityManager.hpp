#ifndef ENTITYMANAGER__HPP
#define ENTITYMANAGER__HPP
//DESCRIPTION
/*
  The entity manager is used to hold all of the entities. It is a
  singleton class which should only hold one instance.
 */

//CLASSES
class EntityManager;

//INCLUDES
#include <vector>
#include <memory>
#include "Entities.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::vector<AbstractEntity*> entityManagerType;

//FUNCTIONS

//BEGIN
class EntityManager {
private:
  EntityManager() {}
  EntityManager(EntityManager const&);
  void operator=(EntityManager const&);

  entityManagerType entityList;
public:
  static EntityManager* getInstance() {
    static EntityManager _instance = EntityManager();
    return &_instance;
  }

  void addEntity(AbstractEntity* entity);
  const AbstractEntity* getEntityByID(incrementType ID);
  const entityManagerType& getEntities();
};


#endif //END ENTITYMANAGER__HPP
