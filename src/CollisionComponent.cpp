#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::COLLISION, bIsParent) {
  
}

CollisionComponent::~CollisionComponent() {

}
