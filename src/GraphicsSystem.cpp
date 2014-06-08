#include "GraphicsSystem.hpp"
#include "EntityManager.hpp"


GraphicsSystem::GraphicsSystem(enumRenderType renderType) :
    renderType(renderType),
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
	
	//grab all of the graphics components
	auto graphicsList = entity->getComponentsByFamily(
	    enumComponentFamily::GRAPHICS);

	//grab all of the physics components
	auto physicsList = entity->getComponentsByFamily(
	    enumComponentFamily::PHYSICS);
	
	//do nothing if these don't exist
	if (graphicsList.size() <= 0 || physicsList.size() <= 0) {
	    continue;
	}
	
	GraphicsComponent* graphicsComponent = static_cast
	    <GraphicsComponent*> (graphicsList.front());
	
	PhysicsComponent* physicsComponent = static_cast
	    <PhysicsComponent*> (physicsList.front());

	if (renderType == enumRenderType::SDL) {
	    //get the graphics component drawable
	    auto drawable = graphicsComponent->getDrawable();
	    if (drawable == nullptr && drawable->getType() == SDL_DRAWABLE_BMP) {
		auto sdlAssetManager = SDLAssetManager::getInstance();
		drawable = sdlAssetManager->getDrawable(
		    graphicsComponent->getDrawableKey());
		graphicsComponent->setDrawable(drawable);
	    }
	    
	    //get the physics component position and orientation
	    auto position = physicsComponent->getPosition();
	    auto orientation = physicsComponent->getOrientation();

	    //draw the drawable with the given position and orientation
	    drawable->draw(position, orientation);

	} //END if (renderType == enumRenderType::SDL) {
    }
}
