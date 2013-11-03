#include "SDLDrawable.hpp"

SDLDrawable::SDLDrawable(SDL_Texture* texture) : AbstractDrawable("SDL"),
						 texture(texture) {
  
}

SDLDrawable::~SDLDrawable() { 
  SDL_DestroyTexture(texture);
  delete sourceRectangle;
}

int SDLDrawable::draw(Vector3 position, 
		      Quaternion orientation) {
  
}

void SDLDrawable::setRect(integerType x, integerType y, integerType w, integerType h) {
  
}

void SDLDrawable::setRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}
