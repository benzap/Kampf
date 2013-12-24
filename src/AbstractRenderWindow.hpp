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
#define DEFAULT_VIRTUAL_SCREEN_WIDTH 800
#define DEFAULT_VIRTUAL_SCREEN_HEIGHT 600

//MACROS

//TYPEDEFS
typedef struct Viewport {
    floatType x; //the x offset
    floatType y; //the y offset
    floatType w; //the width
    floatType h; //the height
} Viewport;

//used for width and height values
typedef struct Resolution {
    integerType w;
    integerType h;
} Resolution;

//FUNCTIONS

//BEGIN
class AbstractRenderWindow {
private:
    //The area that is being viewed on the screen.
    Viewport viewport = {
	0,0,
	DEFAULT_VIRTUAL_SCREEN_WIDTH,
	DEFAULT_VIRTUAL_SCREEN_HEIGHT
    };

    //The virtual resolution of the screen
    Resolution resolution = {
	DEFAULT_VIRTUAL_SCREEN_WIDTH,
	DEFAULT_VIRTUAL_SCREEN_HEIGHT
    };

protected:
    int windowWidth;
    int windowHeight;
public:
    AbstractRenderWindow(int windowWidth = DEFAULT_VIRTUAL_SCREEN_WIDTH,
			 int windowHeight = DEFAULT_VIRTUAL_SCREEN_HEIGHT);
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

    //get the actual window's dimensions
    virtual const std::vector<int> getWindowSize();
    virtual void setWindowSize(floatType w, floatType h);

    //get the current viewport
    const Viewport* getViewport();
    void setViewport(Viewport viewport);
    void setViewport(integerType x,
		     integerType y,
		     integerType w,
		     integerType h);

    const Resolution* getResolution();
    void setResolution(floatType w, floatType h);
};
#endif //END ABSTRACTRENDERWINDOW__HPP
