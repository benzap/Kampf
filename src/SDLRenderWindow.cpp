#include "SDLRenderWindow.hpp"

SDLRenderWindow::SDLRenderWindow(int windowWidth, int windowHeight) :
  AbstractRenderWindow(windowWidth, windowHeight) {
  
}

SDLRenderWindow::~SDLRenderWindow() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void SDLRenderWindow::draw(AbstractDrawable* drawable, 
			   Vector3 position,
			   Quaternion orientation) {
  if (drawable->getType() == "SDL") {
    SDLDrawable* sdl_drawable = static_cast<SDLDrawable*> (drawable);
    sdl_drawable->setRenderer(renderer);
    sdl_drawable->draw(position,
		       orientation);
  }
}

bool SDLRenderWindow::initialize() {
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  this->window = SDL_CreateWindow(this->windowTitle.c_str(),
				  this->xPosition,
				  this->yPosition,
				  this->windowWidth,
				  this->windowHeight,
				  this->windowFlags);
  
  this->renderer = SDL_CreateRenderer(this->window, -1,
				      this->rendererFlags);
}

bool SDLRenderWindow::reinitialize() {
  
}

void SDLRenderWindow::setWindowFlags(Uint32 windowFlags) {
  this->windowFlags = windowFlags;
}

void SDLRenderWindow::setRendererFlags(Uint32 rendererFlags) {
  this->rendererFlags = rendererFlags;
}

void SDLRenderWindow::setPosition(int xPosition, int yPosition) {
  this->xPosition = xPosition;
  this->yPosition = yPosition;
}

void SDLRenderWindow::setTitle(stringType title) {
  this->windowTitle = title;
}
