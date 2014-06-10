#ifndef GRAPHICSSYSTEM__HPP
#define GRAPHICSSYSTEM__HPP
//DESCRIPTION
/*
  Graphics system handles the drawing and display of graphics
 */

//CLASSES
class GraphicsSystem;

//INCLUDES
#include <memory>
#include <iostream>
#include <set>

#include "AbstractSystem.hpp"
#include "RenderWindows.hpp"
#include "SDLAssetManager.hpp"
#include "GraphicsComponent.hpp"

//ENUMS

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//graphics set comparison function
struct graphicsComp {
    bool operator() (GraphicsComponent* first,
		     GraphicsComponent* second) {
	return (first->getIndex() < second->getIndex());
    }
};

//BEGIN
class GraphicsSystem : public AbstractSystem {
private:
    enumRenderType renderType;
public:
    GraphicsSystem(enumRenderType);
    virtual ~GraphicsSystem();
    
    void createMessages();
    void process();

    void processGraphicsComponent(GraphicsComponent*);

};


#endif //END GRAPHICSSYSTEM__HPP
