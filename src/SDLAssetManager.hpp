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

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::unordered_map<stringType, SDLDrawable> textureContainer;

//FUNCTIONS

//BEGIN
class SDLAssetManager {
private:
SDLAssetManager() {}
SDLAssetManager(SDLAssetManager const&);
void operator=(SDLAssetManager const&);

public:
static SDLAssetManager* getInstance() {
static SDLAssetManager _instance = SDLAssetManager();
return &_instance;
}

void addSurface(stringType, SDL_Surface*);
  
};

#endif //END SDLASSETMANAGER__HPP
