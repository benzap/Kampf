#include "GraphicsSystem.hpp"
#include <memory>
#include <iostream>
#include "EntityManager.hpp"


GraphicsSystem::GraphicsSystem() :
  AbstractSystem("Graphics") {

}

GraphicsSystem::~GraphicsSystem() {

}

void GraphicsSystem::createMessages() {

}

void GraphicsSystem::process() {
  //get the entity manager
  auto entityManager = EntityManager::getInstance();
  for (auto entity : entityManager->getEntities()) {
    for (auto component : entity->getComponentsByFamily(enumComponentFamily::GRAPHICS)) {
      auto graphicsComponent = std::static_pointer_cast<GraphicsComponent> (component);


      std::cout << "draw" << std::endl;


    }
  }
}
