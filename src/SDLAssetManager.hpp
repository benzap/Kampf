#ifndef SDLASSETMANAGER__HPP
#define SDLASSETMANAGER__HPP
//DESCRIPTION
/*
  Holds all of the textures that will be used to represent the game
*/

//CLASSES
class SDLAssetManager;

//INCLUDES
#include <unordered_map>

#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLDrawable.hpp"
#include "SDLRenderWindow.hpp"

//DEFINITIONS

//MACROS
#define FULL_ASSET NULL

//TYPEDEFS
typedef std::unordered_map<stringType, SDLDrawable> textureContainerType;

//FUNCTIONS

//BEGIN
class SDLAssetManager {
private:
  SDLAssetManager() {}
  SDLAssetManager(SDLAssetManager const&);
  void operator=(SDLAssetManager const&);
  
  textureContainerType textureContainer;
  SDLRenderWindow* renderer;
public:
  static SDLAssetManager* getInstance() {
    static SDLAssetManager _instance = SDLAssetManager();
    return &_instance;
  }

  void setRenderer(AbstractRenderWindow*);

  //add an SDL surface to the asset manager, where only the section
  //defined by the generated texture is stored in the manager 
  SDLDrawable* addSurface(const stringType&, SDL_Surface*, SDL_Rect* = FULL_ASSET);

  //add a BMP to the asset manager, where only the section defined by
  //the SDL_Rect will be used by the generated texture stored in the
  //manager
  SDLDrawable* addBMP(const stringType&, const stringType&, SDL_Rect* = FULL_ASSET);

  boolType hasDrawable(const stringType&);
  SDLDrawable* getDrawable(const stringType&);
  boolType removeDrawable(const stringType&);

};

#endif //END SDLASSETMANAGER__HPP
