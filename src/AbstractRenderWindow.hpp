#ifndef ABSTRACTRENDERWINDOW__HPP
#define ABSTRACTRENDERWINDOW__HPP
//DESCRIPTION
/*
  Used to hold the SDL Window that represents the context
 */

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractDrawable.hpp"

//CLASSES
class AbstractRenderWindow;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class AbstractRenderWindow{
private:

protected:
  int windowWidth;
  int windowHeight;
public:
  AbstractRenderWindow(int windowWidth = 800, int windowHeight = 600);
  virtual ~AbstractRenderWindow();

  virtual bool reinitialize() = 0;
  virtual bool initialize() = 0;
  virtual void draw(AbstractDrawable* drawable,
		    Vector3 position,
		    Quaternion orientation) = 0;

  
};

#endif //END ABSTRACTRENDERWINDOW__HPP
