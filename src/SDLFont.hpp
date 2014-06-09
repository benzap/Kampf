#ifndef SDLFONT__HPP
#define SDLFONT__HPP
//DESCRIPTION
/*
  Font representation for TTF_Font which is being wrapped to allow
  easier lua binding.
 */

//CLASSES
class SDLFont;

//INCLUDES
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class SDLFont {
private:
    
public:
    SDLFont();
    virtual ~SDLFont();
};

#endif //END SDLFONT__HPP
