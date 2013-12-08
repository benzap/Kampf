#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::COLLISION, bIsParent) {
  
}

CollisionComponent::~CollisionComponent() {

}

std::shared_ptr<AbstractComponent> CollisionComponent::createChild(
    stringType name) {
    auto component = std::shared_ptr<AbstractComponent>
	(new CollisionComponent(name, false));
    
    this->addChild(component);
    return component;
}
