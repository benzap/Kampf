#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

/* INCLUDES */

#include <string>

#include "Object.hpp"


//******

/* TYPEDEFS */
typedef std::string PATH_TYPE;
typedef unsigned int type_count;

//Handles the objects and their changes in state
class StateMachine{
private:
  ObjectPtrPtr objectList;
  type_count objectCount;
  bool bKeepRunning;
  
public:
  StateMachine(); ~StateMachine();

  CALLBACK run();

  //This will be expanded to grab a world object and begin executing it
  CALLBACK appendObject(ObjectPtr);
  CALLBACK removeObject(void*, bool);


};



#endif //STATE_MACHINE_HPP
