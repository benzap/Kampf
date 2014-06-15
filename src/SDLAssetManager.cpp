#include "SDLAssetManager.hpp"
#include <cassert>

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
    drawableContainer.insert(drawablePair);
    
    return &drawableContainer[name];
}

SDLDrawable* SDLAssetManager::addBMP(
    stringType name,
    const stringType& filename,
    SDL_Rect* rect) {
    
    SDL_Surface* sdlSurface = SDL_LoadBMP(filename.c_str());

    SDLDrawable* sdlDrawable = nullptr;
    if (sdlSurface != NULL) {
	sdlDrawable = this->addSurface(name, sdlSurface, rect);
	//SDL_FreeSurface(sdlSurface);
    }
    else {
	std::cerr << "Error: in file - " << filename << std::endl;
	std::cerr << SDL_GetError() << std::endl;
    }
    return sdlDrawable;
}

SDLDrawable* SDLAssetManager::addImage(
				       stringType name,
				       const stringType& filename,
				       SDL_Rect* rect) {
    SDL_Surface* sdlSurface = IMG_Load(filename.c_str());
    
    SDLDrawable* sdlDrawable = nullptr;
    if (sdlSurface != NULL) {
	sdlDrawable = this->addSurface(name, sdlSurface, rect);
	//SDL_FreeSurface(sdlSurface);
    }
    else {
	std::cerr << "Error: in file - " << filename << std::endl;
	std::cerr << IMG_GetError() << std::endl;
    }
    return sdlDrawable;
}

boolType SDLAssetManager::hasDrawable(const stringType& name) {
    if (drawableContainer.find(name) != drawableContainer.end()) {
	return true;
    }
    return false;
}

SDLDrawable* SDLAssetManager::getDrawable(const stringType& name) {
    assert(this->hasDrawable(name));
    return &drawableContainer[name];
}

boolType SDLAssetManager::removeDrawable(const stringType& name) {
    drawableContainer.erase(name);
}

SDLDrawable* SDLAssetManager::copyDrawable(const stringType& srcName,
					   const stringType& destName) {
    assert(this->hasDrawable(srcName));
    SDLDrawable* drawable = this->getDrawable(srcName);
    SDLDrawable newDrawable = drawable->clone();
    
    auto drawablePair = std::pair<stringType, SDLDrawable>(destName, newDrawable);
    drawableContainer.insert(drawablePair);
    
    return &drawableContainer[destName];
}

void SDLAssetManager::setWindowContext(SDLRenderWindow* windowContext) {
    this->windowContext = windowContext;
}

SDLText* SDLAssetManager::addText(stringType name) {
    assert(windowContext != nullptr);

    SDLText sdlText = SDLText(windowContext);
    
    auto textPair = std::pair<stringType, SDLText>(name, sdlText);
    textContainer.insert(textPair);

    return &textContainer[name];
}

boolType SDLAssetManager::hasText(stringType name) {
    if (textContainer.find(name) != textContainer.end()) {
	return true;
    }
    return false;
}

SDLText* SDLAssetManager::getText(stringType name) {
    return &textContainer[name];
}

boolType SDLAssetManager::removeText(stringType name) {
    textContainer.erase(name);
}
