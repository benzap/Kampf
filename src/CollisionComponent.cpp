#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::COLLISION, bIsParent) {
  
}

CollisionComponent::~CollisionComponent() {

}

AbstractComponent* CollisionComponent::createChild(
    stringType name) {
    auto component = new CollisionComponent(name, false);
    
    this->addChild(component);
    return component;
}
