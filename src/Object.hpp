#ifndef OBJECT_HPP
#define OBJECT_HPP

/* DEFINITIONS */

#define CHILDREN_SIZE 5
#define NAME_SIZE 32
/* ENUMERATION */
//CALLBACK in kampf_general.hpp

enum enum_objectTypes {
  NONE,
  WORLD,
  EMPTY,
  AUDIO,
  GRAPHICS,
  GEOMETRY,
  NETWORK,
  DATA,
};

/* CLASSES */
class Object;


/* INCLUDES */
#include <string>
#include "kampf_general.hpp"


/* TYPEDEFS */
typedef long unsigned int ID_TYPE;
typedef Object** ObjectPtrPtr;
typedef Object* ObjectPtr;

/* BEGIN */
class Object{
private:
  char* name;
  bool bIsChild;
  ID_TYPE id;

  int numChildren;
  ObjectPtr parent;

protected:
  enum_objectTypes type;
  ObjectPtrPtr children;
public:
  Object(); 

  virtual ~Object();

  //main part of the object that is executed
  virtual CALLBACK execute();

  virtual void printStatus();

  virtual void logStatus();

  //used to append more children within the object
  CALLBACK appendChild(Object*);

  const ObjectPtr getChildById(ID_TYPE);
  const ObjectPtr getChildByName(char*);
  const ObjectPtr getChildByIndex(unsigned short int);

  //used to remove a specific object from the children by UUID
  CALLBACK removeChildByIdentifier(ID_TYPE);

  //used to remove a specific object by it's memory address
  CALLBACK removeChildByReference(void*);

  int readNumberOfChildren();

  void setID(int);

  ID_TYPE getID();

  void setName(char*);
  
  const char* getName();

  void setParent(ObjectPtr);

  const ObjectPtr getParent();



};

#endif //OBJECT_HPP
