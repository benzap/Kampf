#ifndef ABSTRACTRENDERWINDOW__HPP
#define ABSTRACTRENDERWINDOW__HPP
//DESCRIPTION
/*!
  @file AbstractRenderWindow.hpp
  @brief Used to hold the SDL Window that represents the context

  The render window handles everything involved with resizing the
  window, setting a virtual resolution, changing the current part of
  the screen to view using the viewport, etc.
*/

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractDrawable.hpp"

//CLASSES
class AbstractRenderWindow;

//DEFINITIONS
//! The default virtual screen width
#define DEFAULT_VIRTUAL_SCREEN_WIDTH 800
//! The default virtual screen height
#define DEFAULT_VIRTUAL_SCREEN_HEIGHT 600

//MACROS

//TYPEDEFS

//! The viewport determines the area of the screen that will currently
//! be viewed.
/*!
  This is heavily dependent on the current virtual resolution.
 */
typedef struct Viewport {
    floatType x; //the x offset
    floatType y; //the y offset
    floatType w; //the width
    floatType h; //the height
} Viewport;

//! Used for storing the virtual resolution, or other width and height
//! values
typedef struct Resolution {
    integerType w;
    integerType h;
} Resolution;

//RenderClearColor
struct RenderClearColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

//FUNCTIONS

//BEGIN 
class AbstractRenderWindow {
private:
    //!The area that is being viewed on the screen.
    Viewport viewport = {
	0,0,
	DEFAULT_VIRTUAL_SCREEN_WIDTH,
	DEFAULT_VIRTUAL_SCREEN_HEIGHT
    };

    //!The virtual resolution of the screen
    Resolution resolution = {
	DEFAULT_VIRTUAL_SCREEN_WIDTH,
	DEFAULT_VIRTUAL_SCREEN_HEIGHT
    };

    RenderClearColor renderClearColor = {
	0,0,0,255
    };

protected:
    //! the width of the window
    int windowWidth;
    //! the height of the window
    int windowHeight;
public:

    //! AbstractRenderWindow constructor
    AbstractRenderWindow(int windowWidth = DEFAULT_VIRTUAL_SCREEN_WIDTH,
			 int windowHeight = DEFAULT_VIRTUAL_SCREEN_HEIGHT);
    virtual ~AbstractRenderWindow();

    //! recreates the current render window with the current
    //! configuration
    virtual bool reinitialize() = 0;

    //! initializes the current render window with the current
    //! configuration
    virtual bool initialize() = 0;

    //! draws the given AbstractDrawable
    /*!
      @param drawable The drawable to be drawn
      @param position The position in which to draw the drawable
      @param orientation The orientation of the drawable
     */
    virtual void draw(AbstractDrawable* drawable,
		      Vector3 position,
		      Quaternion orientation) = 0;

    //! after drawing, update the render target to show the results
    virtual boolType update() = 0;
    //! clear the screen before we draw onto the screen again
    virtual boolType clear() = 0;

    //! get the actual window's dimensions.
    /*!
      Returns a two element vector holding the dimensions of the window
     */
    virtual const std::vector<int> getWindowSize();

    //! sets the window size
    /*!
      Sets the window size. Casts to an integer value
      @TODO change to integer type
     */
    virtual void setWindowSize(floatType w, floatType h);

    //! get the current viewport
    const Viewport* getViewport();

    //! set the current viewport to the given viewport
    void setViewport(Viewport viewport);

    //! set the current viewport to have the given parameters
    void setViewport(integerType x,
		     integerType y,
		     integerType w,
		     integerType h);

    //! gets the current virtual resolution
    const Resolution* getResolution();

    //! sets the current virtual resolution
    void setResolution(floatType w, floatType h);

    //! gets the scaled width factor
    /*!
      
      The scaled width factor is used to correct for the difference
      between the current window width, and the current virtual
      resolution width.
    */
    virtual floatType getScaledWidthFactor();
    //! gets the scaled height factor
    /*!
      
      The scaled height factor is used to correct for the difference
      between the current window height, and the current virtual
      resolution height.
    */
    virtual floatType getScaledHeightFactor();

    virtual stringType getTitle() = 0;
    virtual void setTitle(stringType) = 0;

    virtual void setWindowIcon(stringType filename) = 0;

    void setRenderClearColor(unsigned char r,
			     unsigned char g,
			     unsigned char b,
			     unsigned char a = 255);
    
    const RenderClearColor& getRenderClearColor();
};
#endif //END ABSTRACTRENDERWINDOW__HPP
