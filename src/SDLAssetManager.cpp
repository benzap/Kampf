#include "SDLAssetManager.hpp"

SDLDrawable* SDLAssetManager::addSurface(
					 stringType name,
					 SDL_Surface* surface,
					 SDL_Rect* rect) {
    assert(windowContext != nullptr);
    SDL_Renderer* sdl_renderer = this->windowContext->getRenderer();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer,
							surface);
  
    auto drawablePair = std::make_pair(name, SDLDrawable(texture));

    if (rect != nullptr) {
	drawablePair.second.setRect(rect);
    }
    drawablePair.second.setWindowContext(windowContext);
    textureContainer.insert(drawablePair);
}

SDLDrawable* SDLAssetManager::addBMP(
    stringType name,
    const stringType& filename,
    SDL_Rect* rect) {
    
    SDL_Surface* sdlSurface = SDL_LoadBMP(filename.c_str());
    this->addSurface(name, sdlSurface, rect);
    //SDL_FreeSurface(sdlSurface);
}


boolType SDLAssetManager::hasDrawable(const stringType& name) {
    if (textureContainer.find(name) != textureContainer.end()) {
	return true;
    }
    return false;
}

SDLDrawable* SDLAssetManager::getDrawable(const stringType& name) {
    return &textureContainer[name];
}

boolType SDLAssetManager::removeDrawable(const stringType& name) {
    textureContainer.erase(name);
}

void SDLAssetManager::setWindowContext(SDLRenderWindow* windowContext) {
    this->windowContext = windowContext;
}
