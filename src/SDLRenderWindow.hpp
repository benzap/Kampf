#ifndef SDLRENDERWINDOW__HPP
#define SDLRENDERWINDOW__HPP
//DESCRIPTION
/*
  Contains a reference to the current render window, which in this
  case, is the SDL render window
*/

//CLASSES
class SDLRenderWindow;

//INCLUDES
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractRenderWindow.hpp"
#include "SDLDrawable.hpp"

//DEFINITIONS

//defaults
//the internal resolution to represent our texture objects rects with
//respect to the current window
#define SDL_INTERNAL_RESOLUTION_WIDTH 800
#define SDL_INTERNAL_RESOLUTION_HEIGHT 600

//MACROS

//ENUM

//TYPEDEFS

//FUNCTIONS

//BEGIN
class SDLRenderWindow : public AbstractRenderWindow {
private:
    int xPosition = SDL_WINDOWPOS_CENTERED;
    int yPosition = SDL_WINDOWPOS_CENTERED;

    //title
    stringType windowTitle = "Kampf Engine - SDL";

    //SDL flags
    Uint32 windowFlags = 0;
    Uint32 rendererFlags = 0;

    //the window where things are drawn
    SDL_Window* window;

    //the renderer used to draw onto the window
    SDL_Renderer* renderer;

public:
    SDLRenderWindow(int windowWidth = SDL_INTERNAL_RESOLUTION_WIDTH,
		    int windowHeight = SDL_INTERNAL_RESOLUTION_HEIGHT);
    virtual ~SDLRenderWindow();
  
    bool reinitialize();
    bool initialize();

    void draw(AbstractDrawable* drawable, 
	      Vector3 position = Vector3(),
	      Quaternion orientation = Quaternion());


    boolType update();
    boolType clear();
  
    void setWindowFlags(Uint32 windowFlags);
    void setRendererFlags(Uint32 rendererFlags);

    //sets the position of the window, equal to x,y in
    // SDL_CreateWindow
    void setPosition(int xPosition, int yPosition);

    void setTitle(stringType title);
    stringType getTitle();


    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    virtual const std::vector<int> getWindowSize();
    virtual void setWindowSize(floatType w, floatType h);

    //deals with providing the right scaling factor, taking into
    //account the current resolution, window size, and viewport width
    //and height
    virtual floatType getScaledWidthFactor();
    virtual floatType getScaledHeightFactor();

    void setWindowIcon(stringType filename);

    void setRenderClearColor(unsigned int r,
			     unsigned int g,
			     unsigned int b,
			     unsigned int a = 255);

};

#endif //END SDLRENDERWINDOW__HPP
