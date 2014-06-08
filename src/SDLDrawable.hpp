#ifndef SDLDRAWABLE__HPP
#define SDLDRAWABLE__HPP
//DESCRIPTION
/*
  The drawable for SDL images. SDL is limited to drawing only 2D.
*/

//CLASSES
class SDLDrawable;

//INCLUDES
#include <iomanip>
#include <vector>

#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractDrawable.hpp"
#include "SDLRenderWindow.hpp"

//DEFINITIONS
#define SDL_DRAWABLE_BMP "SDL_DRAWABLE_BMP"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class SDLDrawable : public AbstractDrawable {
private:
    //the surface that the drawable will be drawing to
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;

    //the area of the texture to draw to the screen
    SDL_Rect* sourceRectangle = nullptr;
    
    SDLRenderWindow* windowContext = nullptr;

public:
    SDLDrawable();
    SDLDrawable(SDL_Surface* surface, SDLRenderWindow* windowContext);
    virtual ~SDLDrawable();

    int draw(Vector3 position = Vector3(), 
	     Quaternion orientation = Quaternion());

    void setRect(SDL_Rect*);
    void setRect(integerType x, integerType y,
		 integerType w, integerType h);
    const SDL_Rect* getRect();

    void setColorKey(unsigned short r,
		     unsigned short g,
		     unsigned short b);
    
    void setWindowContext(SDLRenderWindow*);

    std::vector<int> getSize();
};

#endif //END SDLDRAWABLE__HPP
