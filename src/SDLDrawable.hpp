#ifndef SDLDRAWABLE__HPP
#define SDLDRAWABLE__HPP
//DESCRIPTION
/*
  The drawable for SDL images. SDL is limited to drawing only 2D.
*/

//CLASSES
class SDLDrawable;

//INCLUDES
#include <vector>

#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"
#include "AbstractDrawable.hpp"
#include "SDLRenderWindow.hpp"

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
    
    SDLRenderWindow* renderer;

public:
    SDLDrawable(SDL_Texture* = nullptr);
    virtual ~SDLDrawable();

    int draw(Vector3 position = Vector3(), 
	     Quaternion orientation = Quaternion());

    void setRect(SDL_Rect*);
    void setRect(integerType x, integerType y,
		 integerType w, integerType h);
    const SDL_Rect* getRect();

    void setRenderer(AbstractRenderWindow*);

    std::vector<int> getTextureSize();
};

#endif //END SDLDRAWABLE__HPP
