#include "GraphicsComponent.hpp"
#include <cassert>

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
    //sets the drawable key
    this->drawableKey = keyString;


    auto sdlAssetManager = SDLAssetManager::getInstance();
    //if we already have a reference to the drawable, then assign the reference
    if (sdlAssetManager->hasDrawable(keyString)) {
	auto drawable = sdlAssetManager->getDrawable(keyString);
	this->setDrawable(drawable);
    }
    //else we set our reference to null and handle it later within the
    //graphics system
    else {
	this->drawableReference = nullptr;
    }
}

stringType GraphicsComponent::getDrawableKey() {
    return this->drawableKey;
}

void GraphicsComponent::setType(stringType drawableType) {
    this->drawableType = drawableType;
}

stringType GraphicsComponent::getType() {
    return this->drawableType;
}

void GraphicsComponent::setIndex(int value) {
    this->zIndex = value;
}

int GraphicsComponent::getIndex() {
    return this->zIndex;
}

GraphicsComponent* createGraphicsComponent(
    stringType name, boolType bIsParent) {
    auto graphicsComponent = new GraphicsComponent(name, bIsParent);
    return graphicsComponent;    
}
