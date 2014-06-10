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
    
    //scrape all of the graphicsList elements into a graphicsSet. This
    //fixes the indexing of our graphics components so they overlap
    //correctly
    std::multiset<GraphicsComponent*, graphicsComp> graphicsSet;

    for (auto entity : entityManager->getEntities()) {
	
	//grab all of the graphics components
	auto graphicsList = entity->getComponentsByFamily(enumComponentFamily::GRAPHICS);

	//insert all of them into the graphics set
	for (auto component : graphicsList) {
	    GraphicsComponent* graphicsComponent = static_cast<GraphicsComponent*> (component);
	    graphicsSet.insert(graphicsComponent);
	}
    }

    //work through the ordered set of graphics components
    for (auto graphicsComponent : graphicsSet) {
	this->processGraphicsComponent(graphicsComponent);
    }
}

void GraphicsSystem::processGraphicsComponent(GraphicsComponent* graphicsComponent) {
    PhysicsComponent* physicsComponent = graphicsComponent->getPhysicsRelation();
	    
    //if we have no physics relation, we can't draw our graphics
    if (physicsComponent == nullptr) {
	//TODO: consider throwing an error?
	return;
    }

    if (renderType == enumRenderType::SDL) {
	//we handle assets differently within SDL based on it's type
	auto sdlAssetManager = SDLAssetManager::getInstance();
	auto drawable = graphicsComponent->getDrawable();
	auto drawableType = graphicsComponent->getType();
	auto drawableKey = graphicsComponent->getDrawableKey();

	//Handling Graphics Drawables
	if (drawableType == SDL_DRAWABLE && drawable == nullptr) {
	    drawable = sdlAssetManager->getDrawable(drawableKey);
	    graphicsComponent->setDrawable(drawable);
	}
	    
	//Handling Text Drawables
	if (drawableType == SDL_TEXT && drawable == nullptr) {
	    drawable = sdlAssetManager->getText(drawableKey);
	    graphicsComponent->setDrawable(drawable);
	}

	//get the physics component position and orientation
	auto position = physicsComponent->getPosition();
	auto orientation = physicsComponent->getOrientation();

	//draw the drawable with the given position and orientation
	drawable->draw(position, orientation);

    } //END if (renderType == enumRenderType::SDL) {    
}
