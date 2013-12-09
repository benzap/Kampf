#include "PhysicsComponent.hpp"
PhysicsComponent::PhysicsComponent(stringType name, bool bIsParent) :
    AbstractComponent(name, enumComponentFamily::PHYSICS, bIsParent) {

}

PhysicsComponent::~PhysicsComponent() {

}

AbstractComponent* PhysicsComponent::createChild(
    stringType name) {
    auto component = new PhysicsComponent(name, false);
    
    this->addChild(component);
    return component;
}

void PhysicsComponent::setPosition(Vector3 position) {
    this->position = position;
}

const Vector3& PhysicsComponent::getPosition() {
    return this->position;
}

void PhysicsComponent::setVelocity(Vector3 velocity) {
    this->velocity = velocity;
}

const Vector3& PhysicsComponent::getVector() {
    return this->velocity;
}
    
void PhysicsComponent::setAcceleration(Vector3 acceleration) {
    this->acceleration = acceleration;
}

const Vector3& PhysicsComponent::getAcceleration() {
    return this->acceleration;
}

void PhysicsComponent::setOrientation(Quaternion orientation) {
    this->orientation = orientation;
}

const Quaternion& PhysicsComponent::getOrientation() {
    return this->orientation;
}

void PhysicsComponent::setDamping(floatType damping) {
    this->damping = damping;
}

floatType PhysicsComponent::getDamping() {
    return this->damping;
}

void PhysicsComponent::setMass(floatType mass) {
    this->inverseMass =  1 / mass;
}

floatType PhysicsComponent::getMass() {
    return 1 / this->inverseMass;
}

PhysicsComponent* createPhysicsComponent(
    stringType name, boolType bIsParent) {
    auto physicsComponent = new PhysicsComponent(name, bIsParent);
    return physicsComponent;
}
