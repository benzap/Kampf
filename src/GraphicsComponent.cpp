#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::GRAPHICS, bIsParent) {
  
}

GraphicsComponent::~GraphicsComponent() {

}

AbstractComponent* GraphicsComponent::createChild(
    stringType name) {
    auto component = new GraphicsComponent(name, false);
    
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

GraphicsComponent* createGraphicsComponent(
    stringType name, boolType bIsParent) {
    auto graphicsComponent = new GraphicsComponent(name, bIsParent);
    return graphicsComponent;    
}
