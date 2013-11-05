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
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void SDLDrawable::setRect(SDL_Rect* rect) {
  this->sourceRectangle = rect;
}

void SDLDrawable::setRect(integerType x, integerType y, 
			  integerType w, integerType h) {
  
}

const SDL_Rect* SDLDrawable::getRect() {
  return sourceRectangle;
}

void SDLDrawable::setRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}

void SDLDrawable::setWindow(SDL_Window* window) {
  this->window = window;
}
