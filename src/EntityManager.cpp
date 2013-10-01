#include "EntityManager.hpp"
#include <algorithm>


void EntityManager::addEntity(AbstractEntity* entity) {
  this->entityList.push_back(entity);
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
