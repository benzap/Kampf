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
  stringType type;

public:
  AbstractDrawable(stringType type);
  virtual ~AbstractDrawable();

  virtual int draw(Vector3 position = Vector3(), 
		   Quaternion orientation = Quaternion()) = 0;

  const stringType& getType();
};

#endif //END ABSTRACTDRAWABLE__HPP
