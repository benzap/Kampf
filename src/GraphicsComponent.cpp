#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(stringType name, bool bIsParent) :
  AbstractComponent(name, enumComponentFamily::GRAPHICS, bIsParent) {
  
}

GraphicsComponent::~GraphicsComponent() {

}

void GraphicsComponent::setDrawable(AbstractDrawable* drawable) {
    this->drawableReference = drawable;
}

AbstractDrawable* GraphicsComponent::getDrawable() {
    return this->drawableReference;
}

void GraphicsComponent::setDrawableKey(stringType keyString) {
    this->drawableKey = keyString;
}

stringType GraphicsComponent::getDrawableKey() {
    return this->drawableKey;
}
