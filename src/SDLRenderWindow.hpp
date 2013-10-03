#ifndef SDLRENDERWINDOW__HPP
#define SDLRENDERWINDOW__HPP
//DESCRIPTION
/*
  Contains a reference to the current render window, which in this
  case, is the SDL render window
 */

//INCLUDES
#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "AbstractRenderWindow.hpp"
//CLASSES
class SDLRenderWindow;

//DEFINITIONS

//MACROS

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

  //the window where things are drawn
  SDL_Window* window;

  //the renderer
  SDL_Renderer* renderer;

  //


public:
  SDLRenderWindow(int windowWidth = 800, int windowHeight = 600);
  virtual ~SDLRenderWindow();

  bool reinitialize();
  bool initialize();

  void draw();

  void setWindowFlags(Uint32 windowFlags);

  //sets the position of the window, equal to x,y in
  // SDL_CreateWindow
  void setPosition(int xPosition, int yPosition);

  void setTitle(stringType title);

};

#endif //END SDLRENDERWINDOW__HPP
