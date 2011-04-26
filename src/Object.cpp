/* INCLUDES */
#include <iostream>
#include <string.h>
#include "kampf_general.hpp"
#include "Object.hpp"



/* START */

Object::Object() {
  this->type = NONE; //this object is inherited, so it's none type
  this->parent = NULL;
  this->name = new char[NAME_SIZE];
  strcpy(this->name, "None");
  this->children = new Object*[CHILDREN_SIZE];
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    this->children[i] = NULL;
  }
  this->numChildren = 0;
  this->id = 0;
  this->bIsChild = false;
}

Object::~Object() {
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    if (this->children[i] == NULL) {
      continue;
    }
    else {
      delete this->children[i];
      this->children[i] = NULL;
    }
  }
  delete [] this->children;
  this->children = NULL;
  delete [] this->name;
  this->name = NULL;
#if DEBUG
       std::cout << "Object terminated < address='" << this << "' type='" 
	 << this->type << "' >" << std::endl;
#endif
}
  
CALLBACK Object::execute() { 
#if DEBUG
  std::cout << "Executing NONE object" << std::endl;
#endif
  return SUCCESS;
}

void Object::printStatus() {
  std::cout << "< Object[" << (void*)this << "]";
  std::cout << " type='NONE" << "'";
  std::cout << " name='" << this->name << "'";
  std::cout << " number_of_children='" << this->numChildren << "'";
  std::cout << " has_parent='" << this->parent << "'";
  std::cout << " >" << std::endl;
}
 
void Object::logStatus() {

}

void Object::setID(int id_) {
  if (parent && id_ == -1) {
    int tempNum = parent->readNumberOfChildren();
    this->id = tempNum + 1;
#if DEBUG
    std::cout << "id# is " << id << std::endl;
#endif    
  }
  else if (parent == NULL) {
#if DEBUG
    std::cout << "id# is 0" << std::endl;
#endif
    this->id = 0;
  }
  else {
    this->id = id_;
  }
}
 
ID_TYPE Object::getID() {
  return this->id;
}
 
void Object::setParent(ObjectPtr parent_) {
  this->parent = parent_;
  if (this->parent != NULL) {
    this->bIsChild = true;
  }
}

const ObjectPtr Object::getParent() {
  return this->parent;
}

void Object::setName(char *string) {
  int length = strlen(string);
  if (length < NAME_SIZE) {
    strcpy(this->name, string);
#if DEBUG
    std::cout << "Set name of object to: " << string << std::endl;
#endif
  }
  else {
    //raise exception

#if DEBUG
    std::cout << "String was too long" << std::endl;
#endif
  }
}

const char* Object::getName() {
  return this->name;
}

CALLBACK Object::appendChild(ObjectPtr child) {
  if (this->numChildren < CHILDREN_SIZE) {
    for (int i = 0; i < CHILDREN_SIZE; i++) {
      if (this->children[i] == NULL) {
	this->children[i] = child;
	child->setParent(this);
	child->setID(-1);
	this->numChildren++;
	return SUCCESS;
      }
    }
  }
  else {
    //later, realloc. Remember to make a new variable that stores the
    //CHILDREN_SIZE
    return FAILED;
  }
  
}


const ObjectPtr Object::getChildById(ID_TYPE id_) {
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    if (this->children[i] == NULL) continue;
    if (this->children[i]->getID() == id_) return this->children[i];
  }
  return NULL; //couldn't find it
}

const ObjectPtr Object::getChildByName(char* name_) {
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    if (this->children[i] == NULL) continue;
    if (!strcmp(this->children[i]->getName(),name_)) return this->children[i];
  }
  return NULL; //couldn't find it
}

const ObjectPtr Object::getChildByIndex(unsigned short int index_) {
  return this->children[index_];
}

CALLBACK Object::removeChildByIdentifier(ID_TYPE id_) {
  bool bFoundID = false;
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    if (this->children[i] == NULL) continue;
    if (this->children[i]->getID() == id_) {
      delete this->children[i];
      this->children[i] = NULL;
      this->numChildren--;
      bFoundID = true;
      break;
    }
  }
  if (!bFoundID) {
#if DEBUG
    std::cout << "Didn't find the id# " << id_ << std::endl;
#endif
    return FAILED;
  }
  else {
#if DEBUG
    std::cout << "Deleted the id# " << id_ << std::endl;
#endif
    return SUCCESS;
  }
}

CALLBACK Object::removeChildByReference(void* address) {
  bool bFoundID = false;
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    if (this->children[i] == NULL) continue;
    if ((void*)this->children[i] == address) {
      delete this->children[i];
      this->children[i] = NULL;
      this->numChildren--;
      bFoundID = true;
      break;
    }
  }
  if (!bFoundID) {
#if DEBUG
    std::cout << "Didn't find the address: " << address << std::endl;
#endif
    return FAILED;
  }
  else {
#if DEBUG
    std::cout << "Deleted the address: " << address << std::endl;
#endif
    return SUCCESS;
  }
}

int Object::readNumberOfChildren() {
  return this->numChildren;
}
