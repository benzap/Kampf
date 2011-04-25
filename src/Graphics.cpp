/* INCLUDES */
#include <iostream>
#include <ctime>
#include "kampf_general.hpp"
#include "Graphics.hpp"

/* START */

Graphics::Graphics(): Object() {
  this->type = GRAPHICS;
  for (int i = 0; i < 3; i++) {
    this->position[i] = 0.;
    this->direction[i] = 0.;
    this->rotation[i] = 0.;
    this->offset[i] = 0.;
    
    this->velocity[i] = 0.;
    this->acceleration[i] = 0.;
    
    this->ang_velocity[i] = 0.;
    this->ang_acceleration[i] = 0.;
  }

  this->startTime = clock();
  for (int i = 0; i < NUM_TEMP_CLOCK_VALUES; i++) {
    this->tempTime[i] = NULL;
    }
  this->endTime = NULL;

  this->state = CREATING;
}

Graphics::~Graphics() {}

void Graphics::printStatus() {
  std::cout << "< Graphics[" << (void*)this << "]";
  std::cout << " type='GRAPHICS'";
  std::cout << " name='" << this->getName() << "'";
  std::cout << " number_of_children='" << this->readNumberOfChildren() << "'";
  std::cout << " has_parent='" << this->getParent() << "'";
  std::cout << " >" << std::endl;
}

CALLBACK Graphics::execute() {
#if DEBUG
  std::cout << "Executing GRAPHICS Object" << std::endl;
#endif
}

CALLBACK Graphics::setPosition(vecValue x, vecValue y, vecValue z) {
  this->position[0] = x;
  this->position[1] = y;
  this->position[2] = (z == HUGE_VAL) ? this->position[2] : z;
  return SUCCESS;
}

CALLBACK Graphics::setDirection(vecValue x, vecValue y, vecValue z) {
  this->direction[0] = x;
  this->direction[1] = y;
  this->direction[2] = (z == HUGE_VAL) ? this->direction[2] : z;
  return SUCCESS;
}

CALLBACK Graphics::setRotation(vecValue x, vecValue y, vecValue z) {
  this->rotation[0] = x;
  this->rotation[1] = y;
  this->rotation[2] = (z == HUGE_VAL) ? this->rotation[2] : z;
  return SUCCESS;
}

const vecValue* Graphics::getPosition() {
  return this->position;
}

const vecValue* Graphics::getDirection() {
  return this->direction;
}

const vecValue* Graphics::getRotation() {
  return this->rotation;
}

CALLBACK Graphics::setVelocity(vecValue x, vecValue y, vecValue z) {
  this->velocity[0] = x;
  this->velocity[1] = y;
  this->velocity[2] = (z == HUGE_VAL) ? this->velocity[2] : z;
  return SUCCESS;
}

CALLBACK Graphics::setAcceleration(vecValue x, vecValue y, vecValue z) {
  this->acceleration[0] = x;
  this->acceleration[1] = y;
  this->acceleration[2] = (z == HUGE_VAL) ? this->acceleration[2] : z;
  return SUCCESS;
}

const vecValue* Graphics::getVelocity() {
  return this->velocity;
}

const vecValue* Graphics::getAcceleration() {
  return this->acceleration;
}

CALLBACK Graphics::setAngularVelocity(vecValue x, vecValue y, vecValue z) {
  this->ang_velocity[0] = x;
  this->ang_velocity[1] = y;
  this->ang_velocity[2] = (z == HUGE_VAL) ? this->ang_velocity[2] : z;
  return SUCCESS;
}

CALLBACK Graphics::setAngularAcceleration(vecValue x, vecValue y, vecValue z) {
  this->ang_acceleration[0] = x;
  this->ang_acceleration[1] = y;
  this->ang_acceleration[2] = (z == HUGE_VAL) ? this->ang_acceleration[2] : z;
  return SUCCESS;
}

const vecValue* Graphics::getAngularVelocity() {
  return this->ang_velocity;
}

const vecValue* Graphics::getAngularAcceleration() {
  return this->ang_acceleration;
}

CALLBACK Graphics::setTempTime(unsigned short index, clockValue cVal) {
  if (index < NUM_TEMP_CLOCK_VALUES) {
    this->tempTime[index] = (cVal == 0) ? clock() : cVal;
    return SUCCESS;
  }
  else {
    return FAILED;
  }
}

CALLBACK Graphics::setEndTime() {
  this->endTime = clock();
}

const clockValue& Graphics::getStartTime() {
  return this->startTime;
}

const clockValue* Graphics::getTempTime(unsigned short index) {
  if (index < NUM_TEMP_CLOCK_VALUES) {
    return this->tempTime + index;
  }
  else {
    return NULL;
  }
}

const clockValue& Graphics::getEndTime() {
  return this->endTime;
}

