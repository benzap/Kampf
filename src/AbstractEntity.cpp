#include "AbstractEntity.hpp"

incrementType AbstractEntity::EntityIncrement = 1;

AbstractEntity::AbstractEntity(stringType name,
			       incrementType id,
			       stringType type) :
  name(name),
  type(type) {
  
  if (id == GENERATE_ID) {
    this->id = AbstractEntity::EntityIncrement++;
  }
  else {
    this->id = id;
  }
  }

AbstractEntity::~AbstractEntity() {

}

const stringType& AbstractEntity::getName() {
  return this->name;
}

void AbstractEntity::setName(stringType name) {
  this->name = name;
}

stringType AbstractEntity::getType() {
  return this->type;
}

incrementType AbstractEntity::getID() {
  return this->id;
}

const componentListType& AbstractEntity::getComponentContainer() {
  return this->componentList;
}

partialComponentListType AbstractEntity::getComponentsByFamily(enumComponentFamily family) {
  auto partCompList = partialComponentListType();
  for (auto component : this->componentList) {
    if (component->getFamily() == family) {
      partCompList.push_back(component);
    }
  }
  return partCompList;
}

partialComponentListType AbstractEntity::getComponentsByName(stringType name) {
  auto partCompList = partialComponentListType();
  for (auto component : this->componentList) {
    if (component->getName() == name) {
      partCompList.push_back(component);
    }
  }
  return partCompList;
}
  
void AbstractEntity::addComponent(AbstractComponent* theComponent) {
  this->componentList.push_back(theComponent);
}

  
