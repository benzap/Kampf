#ifndef SDLTEXT__HPP
#define SDLTEXT__HPP
//DESCRIPTION
/*
  Represents a piece of text, and inherits from abstractdrawable
*/

//CLASSES
class SDLText;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "AbstractDrawable.hpp"

//DEFINITIONS
#define SDL_TEXT "SDL_TEXT"

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class SDLText : public AbstractDrawable {
private:
    

public:
    SDLText();
    virtual ~SDLText();

    virtual int draw(Vector3 position = Vector3(), 
		     Quaternion orientation = Quaternion()) = 0;


};

#endif //END SDLTEXT__HPP
