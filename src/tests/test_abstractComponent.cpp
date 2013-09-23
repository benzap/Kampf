#include <iostream>
#include <cassert>

#include "AbstractComponent.hpp"

int main(int argc, char *argv[]) {
  std::cout << "Test Case" << std::endl;
  auto component = AbstractComponent(stringType("Some Name"));

  assert(component.getName() == "Some Name");
  component.setName(stringType("New Name"));
  assert(component.getName() == "New Name");
	 
  

  return 0;
}
