#include "SDLAssetManager.hpp"

SDLDrawable* SDLAssetManager::addSurface(
    const stringType& name,
    SDL_Surface* surface,
    SDL_Rect* rect) {
  assert(renderer != nullptr);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  
  auto sdlDrawable = SDLDrawable(texture);
  sdlDrawable.setRect(rect);
  sdlDrawable.setRenderer(renderer);
}

SDLDrawable* SDLAssetManager::addBMP(
    const stringType& name,
    const stringType& filename,
    SDL_Rect* rect) {
  SDL_Surface* sdlSurface = SDL_LoadBMP(filename.c_str());
  this->addSurface(name, sdlSurface, rect);
}


boolType SDLAssetManager::hasDrawable(const stringType& name) {
  if (textureContainer.find(name) != textureContainer.cend()) {
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

void SDLAssetManager::setRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}
