#ifndef ABSTRACTDRAWABLE__HPP
#define ABSTRACTDRAWABLE__HPP
//DESCRIPTION
/*
  the drawable, which is an object representing something to be drawn
  on the screen
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"

//CLASSES
class AbstractDrawable;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class AbstractDrawable {
private:
  //its current position
  Vector3 position;
  
  //the offset from the position
  Vector3 offset;
  
  //the center of rotation
  Vector3 origin;

  //the scaling
  Vector3 scale;
  
  Quaternion orientation;

  stringType type;

public:
  AbstractDrawable(stringType type);
  virtual ~AbstractDrawable();

  virtual int draw() = 0;

};

#endif //END ABSTRACTDRAWABLE__HPP
