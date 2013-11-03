#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_mainEntity.cpp");

  auto entity = MainEntity("Some Entity");
  
  TEST_EQUAL(entity.getName(), "Some Entity",
	     "getName()");

  TEST_EQUAL(entity.getType(), ENTITY_MAIN_TYPE,
	     "getType()");

  entity.setName("Hello");
    
  TEST_EQUAL(entity.getName(), "Hello",
	     "setName()");

  auto entity2 = MainEntity("Second Entity", 3);
  TEST_EQUAL(entity2.getID(), 3,
	     "getID()");

  auto component = std::shared_ptr<AbstractComponent>
    (new AbstractComponent("Some Component"));
  
  entity2.addComponent(component);

  auto abstractList = entity2.getComponentsByFamily(enumComponentFamily::ABSTRACT);
  TEST_EQUAL(abstractList.front()->getName(), component->getName(),
	     "getComponentsByFamily()");

  auto abstractList2 = entity2.getComponentsByName("Some Component");

  TEST_EQUAL(abstractList2.front()->getName(), component->getName(),
	     "getComponentsByName()");
  
  TEST_EQUAL(entity2.getComponentContainer()[0]->getName(),
	     component->getName(),
	     "getComponentContainer()");


  return 0;
}
