//Start of program
#include <iostream>

#include "kampf_general.hpp"
#include "main.hpp"
#include "StateMachine.hpp"
#include "Object.hpp"
#include "Empty.hpp"
#include "Data.hpp"
#include "Graphics.hpp"

int main() {

  StateMachine* sm = new StateMachine();
  
  //object appending
  Empty* theObject = new Empty();
  theObject->setName("First Empty");
  


  int* value = new int[2];
  value[0] = 5;
  value[1] = 2;

  Data<int*>* dataObject = new Data<int*>(value,2,true);
  theObject->appendChild(dataObject);

  float* fvalue = new float[2];
  fvalue[0] = 0.1;
  fvalue[1] = 0.2;
  
  Data<float*>* dataObject2 = new Data<float*>(fvalue,2,true);
  theObject->appendChild(dataObject2);

  Graphics* gObject1 = new Graphics();
  theObject->appendChild(gObject1);

  int check;
  check = sm->appendObject(theObject);
  if (check == SUCCESS) {
    std::cout << "running statemachine" << std::endl;
    sm->run();
    std::cout << "ran statemachine" << std::endl;
  }
  else {
    std::cout << "Append failed" << std::endl;
  }

  gObject1->setName("The Graphics Object");

  const clockValue c = clock() + 1200;
  gObject1->setTempTime(0,c);
  clockValue* cPtr = gObject1->getTempTime(0);
  std::cout << clock() << " : " << *cPtr << std::endl;


  //print the status of each
  theObject->printStatus();  
  dataObject->printStatus();
  dataObject2->printStatus();
  gObject1->printStatus();

  //cleanup

  delete sm; //StateMachine

  return 0;

}
