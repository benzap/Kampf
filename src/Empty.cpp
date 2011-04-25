/* INCLUDES */
#include <iostream>

#include "kampf_general.hpp"
#include "Empty.hpp"
#include "Object.hpp"


/* START */

Empty::Empty(): Object() {
  this->type = EMPTY;
}

Empty::~Empty() {

}


void Empty::printStatus() {
  std::cout << "< Empty[" << (void*)this << "]";
  std::cout << " type='EMPTY" << "'";
  std::cout << " name='" << this->getName() << "'";
  std::cout << " number_of_children='" << this->readNumberOfChildren() << "'";
  std::cout << " has_parent='" << this->getParent() << "'";
  std::cout << " >" << std::endl;
}

CALLBACK Empty::execute() {
#if DEBUG
  std::cout << "Executing EMPTY Object" << std::endl;
#endif
  for (int i = 0; i < CHILDREN_SIZE; i++) {
    if (this->children[i] == NULL) {
      continue;
    }
    else {
      this->children[i]->execute();
    }
  }
}
