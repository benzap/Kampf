#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::PHYSICS, bIsParent) {

}

PhysicsComponent::~PhysicsComponent() {

}
