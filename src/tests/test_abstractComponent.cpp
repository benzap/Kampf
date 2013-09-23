#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_abstractComponent.cpp");

  auto component = AbstractComponent(stringType("Some Name"));

  TEST_EQUAL(component.getName(), "Some Name",
	     "getName()");

  component.setName(stringType("New Name"));
  TEST_EQUAL(component.getName(), "New Name",
	     "setName()");
	 
  //checking component stuff
  component.setCustomAttribute("Test", 12);
  auto iTest = component.getCustomAttribute_int("Test");
  TEST_EQUAL(iTest, 12,
	     "getCustomAttribute_int()");

  TEST_BOOL(component.hasCustomAttribute("Test"), 
	    "hasCustomComponent");







  return 0;
}
