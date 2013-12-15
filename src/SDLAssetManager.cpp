#include "SDLAssetManager.hpp"

SDLDrawable* SDLAssetManager::addSurface(
					 stringType name,
					 SDL_Surface* surface,
					 SDL_Rect* rect) {
    assert(windowContext != nullptr);

    if (surface == nullptr) {
	std::cerr << "Warning: unable to add surface to asset manager";
	std::cerr << std::endl;
	std::cerr << SDL_GetError() << std::endl;
    }

    SDLDrawable drawable = SDLDrawable(surface, windowContext);
    
    if (rect != nullptr) {
	drawable.setRect(rect);
    }
    auto drawablePair = std::pair<stringType, SDLDrawable>(name, drawable);
    //textureContainer[name] = drawable;
    textureContainer.insert(drawablePair);
}

SDLDrawable* SDLAssetManager::addBMP(
    stringType name,
    const stringType& filename,
    SDL_Rect* rect) {
    
    SDL_Surface* sdlSurface = SDL_LoadBMP(filename.c_str());
    
    if (sdlSurface != NULL) {
	this->addSurface(name, sdlSurface, rect);
	//SDL_FreeSurface(sdlSurface);
    }
    else {
	std::cerr << "Error: in file - " << filename << std::endl;
	std::cerr << SDL_GetError() << std::endl;
    }
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
