#ifndef COLLISIONCOMPONENT__HPP
#define COLLISIONCOMPONENT__HPP
//DESCRIPTION
/*
  Includes the collision component, which is used to resemble an
  entities collision with another entity. Entities can consist of
  several collision components within a hierarchy, with deeper
  hierachies resembling more finely honed pieces to encompass the
  thing that we are checking against.
  
  It's important to note that a collision component's is primarily
  affected by the positioning of the physics component.

*/

//CLASSES
class CollisionComponent;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractComponent.hpp"
#include "PhysicsComponent.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//ENUM
//bounding volumes defined by [ericson05] S4.1
enum class enumCollisionType {
    NONE,
    PARENT,
    CIRCLE,
    SQUARE,
    AABB,
    OBB,
    EDOP,
    CONVEX, 
};

//FUNCTIONS

//BEGIN
class CollisionComponent : public AbstractComponent {
private:
    //the collision component is bound to a physics component.
    PhysicsComponent* physicsRelation = nullptr;
    //the offset of the collision component
    //relative to the physics component
    Vector3 offset;
    //it's center of rotation
    Vector3 origin;
    Quaternion orientation;

    //the type of collision component
    enumCollisionType collisionType = enumCollisionType::NONE;
    
    //need to store info based on collision component type
    //used by CIRCLE
    floatType radius = 0;
    //used by AABB, OBB
    floatType width = 0;
    floatType height = 0;
    //used by EDOP and CONVEX
    std::vector<Vector3> vectorList;

public:
    CollisionComponent(stringType name, 
		       bool bIsParent = true);
  
    virtual ~CollisionComponent();
    virtual AbstractComponent* createChild(stringType name);

    void setCollisionType(enumCollisionType);
    enumCollisionType getCollisionType();

    void setCollisionTypeString(stringType);
    stringType getCollisionTypeString();

    void setRadius(floatType);
    floatType getRadius();

    void setWidth(floatType);
    floatType getWidth();

    void setHeight(floatType);
    floatType getHeight();

    void setVectorList(std::vector<Vector3>);
    std::vector<Vector3> getVectorList();
};

#endif //END COLLISIONCOMPONENT__HPP
