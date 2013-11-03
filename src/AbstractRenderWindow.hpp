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

  //after drawing, update the render target to show the results
  virtual boolType update() = 0;
  //clear the screen before we draw onto the screen againx
  virtual boolType clear() = 0;
};

#endif //END ABSTRACTRENDERWINDOW__HPP
