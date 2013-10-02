#include "kampf.hpp"

Kampf::Kampf() : 
  windowContext(nullptr),
  messenger(nullptr),
  ruleMachine(nullptr) {
}

Kampf::~Kampf() {

}

void Kampf::runMainLoop() {

}
  
const AbstractRenderWindow* Kampf::getRenderWindow() {
  return this->windowContext;
}

const AbstractSystem* Kampf::getSystem(stringType systemType) {
  return nullptr;
}

const Messenger* Kampf::getMessenger() {
  return this->messenger;
}

const RuleMachine* Kampf::getRuleMachine() {
  return this->ruleMachine;
}
