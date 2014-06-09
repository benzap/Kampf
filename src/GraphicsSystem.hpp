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

#include "AbstractSystem.hpp"
#include "RenderWindows.hpp"
#include "SDLAssetManager.hpp"

//ENUMS

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class GraphicsSystem : public AbstractSystem {
private:
    enumRenderType renderType;
public:
    GraphicsSystem(enumRenderType);
    virtual ~GraphicsSystem();
    
    void createMessages();
    void process();
};


#endif //END GRAPHICSSYSTEM__HPP
