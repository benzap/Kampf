#ifndef SDLDRAWABLE__HPP
#define SDLDRAWABLE__HPP
//DESCRIPTION
/*
  The drawable for SDL images. SDL is limited to drawing only 2D.
 */

//CLASSES
class SDLDrawable;

//INCLUDES
#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractDrawable.hpp"


//DEFINITIONS
#define SDL_DRAWABLE_TYPE "SDL"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class SDLDrawable : public AbstractDrawable {
private:
  //the surface that the drawable will be drawing to
  SDL_Texture* texture = nullptr;

  //the area of the texture to draw to the screen
  SDL_Rect* sourceRectangle = nullptr;

  //the renderer reference used to draw to the window
  SDL_Renderer* renderer = nullptr;

  //the window reference
  SDL_Window* window = nullptr;

public:
  SDLDrawable(SDL_Texture* = nullptr);
  virtual ~SDLDrawable();

  int draw(Vector3 position = Vector3(), 
	   Quaternion orientation = Quaternion());

  void setRect(SDL_Rect*);
  void setRect(integerType x, integerType y,
	       integerType w, integerType h);
  const SDL_Rect* getRect();

  void setRenderer(SDL_Renderer*);
  void setWindow(SDL_Window*);
};

#endif //END SDLDRAWABLE__HPP
