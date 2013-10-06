#include <iostream>
#include <cassert>

#include "KF_test.hpp"

int main(int argc, char *argv[]) {
  TEST_NAME("test_messenger.cpp");

  auto messenger = Messenger::getInstance();
  auto msg1 = messenger->appendMessage();

  msg1->firstEntity = new AbstractEntity("some entity");
  msg1->firstComponent = nullptr;
  
  msg1 = messenger->appendMessage();
  msg1->firstEntity = new AbstractEntity("some other entity");

  TEST_EQUAL(messenger->retrieveMessages().size(), 2,
	     "messenger retrieve messages");

  TEST_BOOL(messenger->retrieveMessages()[0].firstEntity != nullptr,
	    "correct referencing");

  
  messenger->clearMessages();

  TEST_EQUAL(messenger->retrieveMessages().size(), 0,
	     "Clear messages works");

  msg1 = messenger->appendMessage();
  msg1->customData["custom value"] = CustomAttribute(12);

  auto msg2 = messenger->retrieveMessages()[0];
  auto intValue = msg2.customData["custom value"].get_int();

  TEST_EQUAL(intValue, 12,
	     "checking custom attributes");
  
  return 0;
}
