#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::GRAPHICS, bIsParent) {
  
}

GraphicsComponent::~GraphicsComponent() {

}
