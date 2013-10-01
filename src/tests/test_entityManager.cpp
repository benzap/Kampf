#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_entityManager.cpp");

  auto entityManager = EntityManager::getInstance();

  auto entity = new AbstractEntity("Some Entity", 10);
  entityManager->addEntity(entity);

  TEST_EQUAL(entityManager->getEntityByID(10), entity,
	     "getEntityByID()");

  TEST_EQUAL(entityManager->getEntities().size(), 1,
	     "getEntities()");


  return 0;
}
