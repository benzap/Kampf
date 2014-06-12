#include "EntityManager.hpp"
#include <algorithm>


incrementType EntityManager::addEntity(AbstractEntity* entity) {
    incrementType id = entity->getID();
    this->entityList.push_back(entity);
    return id;
}

const AbstractEntity* EntityManager::getEntityByID(incrementType ID) {
  for(auto entity : this->entityList) {
    if (entity->getID() == ID) {
      return entity;
    }
  }
  return nullptr;
}

const entityManagerType& EntityManager::getEntities() {
  return this->entityList;
}
