/* INCLUDES */
#include "kampf_general.hpp"
#include "StateMachine.hpp"
#include "Object.hpp"


/* DEFINITIONS */

#define SM_LIST_SIZE 5

/* START */

StateMachine::StateMachine() {
  this->objectList = new Object*[SM_LIST_SIZE];
  for (int i = 0; i < SM_LIST_SIZE; i++) {
    this->objectList[i] = NULL;
  }
#if DEBUG
  std::cout << "sizeof(objectList): " << sizeof(this->objectList) << std::endl;
#endif
  this->objectCount = 0;
  this->bKeepRunning = true;
}

StateMachine::~StateMachine() {
  for (int i = 0; i < SM_LIST_SIZE; i++) {
    if (this->objectList[i] == NULL) {
      continue;
    }
    else {
      delete this->objectList[i];
      this->objectList[i] = NULL;
    }
  }
  delete [] this->objectList;
  this->objectList = NULL;
}

CALLBACK StateMachine::run() {
  while(this->bKeepRunning) {
    for (int i = 0; i < SM_LIST_SIZE; i++) {
      if (this->objectList[i] == NULL) {
	continue;
      }
      else {
#if DEBUG
	std::cout << "executing: ";
	this->objectList[i]->printStatus();
#endif
	this->objectList[i]->execute();
      }
    }
    this->bKeepRunning = false; //change this in actual operation
  }
  return SUCCESS;
}

CALLBACK StateMachine::appendObject(Object* theObject) {
  for (int i = 0; i < SM_LIST_SIZE; i++) {
    if (this->objectList[i] != NULL) continue;
    this->objectList[i] = theObject;
    this->objectCount++;
    return SUCCESS;
#if DEBUG
    std::cout << "appended object" << std::endl;
#endif
  }
  return FAILED;
}

CALLBACK StateMachine::removeObject(void* address, bool bDelete=true) {
  for (int i = 0; i < SM_LIST_SIZE; i++) {
    if (this->objectList[i] == NULL) continue;
    if ((void*) this->objectList[i] == address) {
      if (bDelete) {
	delete this->objectList[i];
      }
      this->objectList[i]= NULL;

      return SUCCESS;
    } 
  }
  return FAILED;
}
