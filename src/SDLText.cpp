#include "SDLText.hpp"

SDLText::SDLText() : AbstractDrawable(SDL_TEXT) {
    
}

SDLText::~SDLText() {

}

int SDLText::draw(Vector3 position,
		  Quaternion orientation) {
    return 0;
}
 
