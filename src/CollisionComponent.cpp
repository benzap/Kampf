#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(stringType name, bool bIsParent) :
    AbstractComponent(name, enumComponentFamily::COLLISION, bIsParent) {
  
}

CollisionComponent::~CollisionComponent() {

}

AbstractComponent* CollisionComponent::createChild(stringType name) {
    auto component = new CollisionComponent(name, false);
    
    this->addChild(component);
    return component;
}

void CollisionComponent::setPhysicsRelation(PhysicsComponent* phys) {
    this->physicsRelation = phys;
}

PhysicsComponent* CollisionComponent::getPhysicsRelation() {
    return this->physicsRelation;
}

void CollisionComponent::setOffset(Vector3 offset) {
    this->offset = offset;
}

const Vector3& CollisionComponent::getOffset() {
    return this->offset;
}
    
void CollisionComponent::setOrigin(Vector3 origin) {
    this->origin = origin;
}

const Vector3& CollisionComponent::getOrigin() {
    return this->origin;
}

void CollisionComponent::setOrientation(Quaternion orientation) {
    this->orientation = orientation;
}

Quaternion CollisionComponent::getOrientation() {
    return this->orientation;
}

void CollisionComponent::setCollisionType(
    enumCollisionType collisionType) {
    this->collisionType = collisionType;
}

enumCollisionType CollisionComponent::getCollisionType() {
    return this->collisionType;
}

void CollisionComponent::setCollisionTypeString(stringType typeString) {
    if (typeString == "NONE") {
	this->collisionType = enumCollisionType::NONE;
    }
    else if (typeString == "PARENT") {
	this->collisionType = enumCollisionType::PARENT;
    }
    else if (typeString == "CIRCLE") {
	this->collisionType = enumCollisionType::CIRCLE;
    }
    else if (typeString == "SQUARE") {
	this->collisionType = enumCollisionType::SQUARE;
    }
    else if (typeString == "AABB") {
	this->collisionType = enumCollisionType::AABB;
    }
    else if (typeString == "OBB") {
	this->collisionType = enumCollisionType::OBB;
    }
    else if (typeString == "EDOP") {
	this->collisionType = enumCollisionType::EDOP;
    }
    else if (typeString == "CONVEX") {
	this->collisionType = enumCollisionType::CONVEX;
    }
    else {
	std::cout << "Warning: Unknown collision type" << std::endl;
	this->collisionType = enumCollisionType::NONE;
    }
}

stringType CollisionComponent::getCollisionTypeString() {
    if (this->collisionType == enumCollisionType::NONE) {
	return "NONE";
    }
    else if (this->collisionType == enumCollisionType::PARENT) {
	return "PARENT";
    }
    else if (this->collisionType == enumCollisionType::CIRCLE) {
	return "CIRCLE";
    }
    else if (this->collisionType == enumCollisionType::SQUARE) {
	return "SQUARE";
    }
    else if (this->collisionType == enumCollisionType::AABB) {
	return "AABB";
    }
    else if (this->collisionType == enumCollisionType::OBB) {
	return "OBB";
    }
    else if (this->collisionType == enumCollisionType::EDOP) {
	return "EDOP";
    }
    else if (this->collisionType == enumCollisionType::CONVEX) {
	return "CONVEX";
    }
    else {
	return "UNKNOWN";
    }
}

void CollisionComponent::setRadius(floatType value) {
    this->radius = value;
}

floatType CollisionComponent::getRadius() {
    return radius;
}

void CollisionComponent::setWidth(floatType value) {
    this->width = value;
}

floatType CollisionComponent::getWidth() {
    return width;
}

void CollisionComponent::setHeight(floatType value) {
    this->height = value;
}

floatType CollisionComponent::getHeight() {
    return this->height;
}

void CollisionComponent::setVectorList(std::vector<Vector3> vectorList) {
    this->vectorList = vectorList;
}

std::vector<Vector3> CollisionComponent::getVectorList() {
    return this->vectorList;
}
