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

  TEST_BOOL(!component.hasCustomAttribute("1234kjfksl"),
	    "hasCustomAttribute false");

  component.setCustomAttribute("Test", 12);
  auto iTest = component.getCustomAttribute_int("Test");
  TEST_EQUAL(iTest, 12,
	     "getCustomAttribute_int()");

  TEST_BOOL(component.hasCustomAttribute("Test"), 
	    "has Test");

  //checking float
  component.setCustomAttribute("Float", 12.4);
  auto fTest = component.getCustomAttribute_float("Float");
  TEST_EQUAL(fTest, 12.4,
	     "getCustomAttribute_float()");

  TEST_BOOL(component.hasCustomAttribute("Float"),
	    "has Float");

  //checking char
  component.setCustomAttribute("Char", 'a');
  auto cTest = component.getCustomAttribute_char("Char");
  TEST_EQUAL(cTest, 'a',
	     "getCustomAttribute_char()");

  TEST_BOOL(component.hasCustomAttribute("Char"),
	    "has Char");

  //checking int array
  auto intArray = intArrayType();
  intArray.push_back(1);
  intArray.push_back(2);
  component.setCustomAttribute("iArray", &intArray);
  
  TEST_EQUAL(&intArray, component.getCustomAttribute_intArray("iArray"),
	     "checking int array valid ptr");

  intArray[0] = 10;
  
  auto intArray2 = *component.getCustomAttribute_intArray("iArray");
  TEST_EQUAL(intArray[0], intArray2[0], "checking int array elements");
  
  //checking float array
  auto floatArray = floatArrayType();
  floatArray.push_back(12.4);
  floatArray.push_back(12.5);
  component.setCustomAttribute("fArray", &floatArray);

  TEST_EQUAL(&floatArray, component.getCustomAttribute_floatArray("fArray"),
	     "checking float array valid ptr");
  
  floatArray[0] = 65;

  auto floatArray2 = *component.getCustomAttribute_floatArray("fArray");
  TEST_EQUAL(floatArray[0], floatArray2[0],
	     "checking float array elements");

  //checking string type
  component.setCustomAttribute("String Value", "Hello there");
  TEST_EQUAL("Hello there", component.getCustomAttribute_string("String Value"),
	     "Equal strings");

  //checking void values
  std::map<bool, int> someMap;
  someMap[true] = 1;
  someMap[false] = 0;
  
  component.setCustomAttribute("void", static_cast<void*>(&someMap));
  TEST_EQUAL(&someMap, static_cast<void*>(component.getCustomAttribute_void("void")),
	     "testing void");

  auto voidMap = component.getCustomAttribute_void("void");
  auto someMap2_ptr = static_cast<std::map<bool, int>*>(voidMap);
  auto someMap2 = *someMap2_ptr;
  TEST_EQUAL(someMap[0], someMap2[0],
	    "checking valid void dereference");

  TEST_EQUAL(component.getCustomAttributeType("void"), enumAttribute::VOID,
	     "test attribute types");

  TEST_BOOL(!component.hasChildren(), "doesn't have children");

  //add child components
  component.createChild("childAbstract1", enumComponentFamily::ABSTRACT);
  TEST_BOOL(component.hasChildren(), "has children");

  auto childList = component.getChildContainer();

  TEST_EQUAL(childList.front()->getName(),"childAbstract1",
	     "checking if valid child");
  
  auto component2 = std::shared_ptr<AbstractComponent> 
    (new AbstractComponent("anotherComponent",
			   enumComponentFamily::ABSTRACT, false));
  
  component.addChild(component2);
  
  TEST_EQUAL(component2->getName(), childList.back()->getName(),
	     "Equal Components");
     
     
  std::cout << childList.back()->getName() << std::endl;


  //deleting keys
  component.deleteCustomAttribute("iArray");
  
  TEST_BOOL(!component.hasCustomAttribute("iArray"),
	    "does not have deleted attribute");

  return 0;
}
