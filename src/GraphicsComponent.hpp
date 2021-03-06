#ifndef GRAPHICSCOMPONENT__HPP
#define GRAPHICSCOMPONENT__HPP
//DESCRIPTION
/*
  The graphics component holds a description of what to draw on the
  screen at any given position. The type of renderer used determines
  how it will draw the component.
*/

//CLASSES
class GraphicsComponent;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractComponent.hpp"
#include "PhysicsComponent.hpp"
#include "AbstractDrawable.hpp"
#include "SDLText.hpp"
#include "SDLDrawable.hpp"
#include "SDLAssetManager.hpp"
//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

GraphicsComponent* createGraphicsComponent(
    stringType name, boolType bIsParent = true);
    
//BEGIN
class GraphicsComponent : public AbstractComponent {
private:
    //the offset from the position
    Vector3 offset;

    //its center of rotation
    Vector3 origin;
  
    //the scaling
    Vector3 scale;

    Quaternion orientation;

    stringType drawableType = SDL_DRAWABLE;

    //the key name of the drawable this graphics component refers to
    stringType drawableKey;

    //an actual reference to the drawable
    AbstractDrawable* drawableReference = nullptr;

    //the depth of the given drawable, to determine when it should be drawn
    int zIndex = 1;

    //the physics relation used for determining the position of this element
    PhysicsComponent* physicsRelation = nullptr;

public:
    GraphicsComponent(stringType name, bool bIsParent = true);
    virtual ~GraphicsComponent();

    virtual AbstractComponent* createChild(stringType name);

    void setDrawable(AbstractDrawable*);
    AbstractDrawable* getDrawable();
    
    void setType(stringType drawableType);
    stringType getType();

    void setDrawableKey(stringType);
    stringType getDrawableKey();

    void setIndex(int);
    int getIndex();

    

    void setPhysicsRelation(PhysicsComponent* physicsRelation);
    PhysicsComponent* getPhysicsRelation();

};

#endif //END GRAPHICSCOMPONENT__HPP
