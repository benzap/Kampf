#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::GRAPHICS, bIsParent) {
  
}

GraphicsComponent::~GraphicsComponent() {

}

std::shared_ptr<AbstractComponent> GraphicsComponent::createChild(
    stringType name) {
    auto component = std::shared_ptr<AbstractComponent>
	(new GraphicsComponent(name, false));
    
    this->addChild(component);
    return component;
}

void GraphicsComponent::setDrawable(AbstractDrawable* drawable) {
    this->drawableReference = drawable;
}

AbstractDrawable* GraphicsComponent::getDrawable() {
    return this->drawableReference;
}

void GraphicsComponent::setDrawableKey(stringType keyString) {
    //go grab the drawable from the asset manager
    this->drawableKey = keyString;
}

stringType GraphicsComponent::getDrawableKey() {
    return this->drawableKey;
}

std::shared_ptr<GraphicsComponent> createGraphicsComponent(
    stringType name, boolType bIsParent) {
    auto graphicsComponent = std::shared_ptr<GraphicsComponent>
	(new GraphicsComponent(name, bIsParent));
    return graphicsComponent;    
}
