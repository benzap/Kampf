#ifndef SDLASSETMANAGER__HPP
#define SDLASSETMANAGER__HPP
//DESCRIPTION
/*
  Holds all of the textures that will be used to represent the game
*/

//CLASSES
class SDLAssetManager;

//INCLUDES
#include <map>
#include <tuple>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLRenderWindow.hpp"
#include "SDLDrawable.hpp"

//DEFINITIONS

//MACROS
#define FULL_ASSET NULL

//TYPEDEFS
typedef std::map<stringType, SDLDrawable> textureContainerType;

//FUNCTIONS

//BEGIN
class SDLAssetManager {
private:
    SDLAssetManager() {}
    SDLAssetManager(SDLAssetManager const&);
    void operator=(SDLAssetManager const&);
  
    textureContainerType textureContainer;
    SDLRenderWindow* windowContext;
public:
    static SDLAssetManager* getInstance() {
	static SDLAssetManager _instance = SDLAssetManager();
	return &_instance;
    }

    void setWindowContext(SDLRenderWindow*);

    //add an SDL surface to the asset manager, where only the section
    //defined by the generated texture is stored in the manager 
    SDLDrawable* addSurface(stringType, SDL_Surface*, SDL_Rect* = nullptr);

    //add a BMP to the asset manager, where only the section defined by
    //the SDL_Rect will be used by the generated texture stored in the
    //manager
    SDLDrawable* addBMP(
			stringType name,
			const stringType& filename,
			SDL_Rect* rect = nullptr);

    SDLDrawable* addImage(
			  stringType name,
			  const stringType& filename,
			  SDL_Rect* rect = nullptr);

    boolType hasDrawable(const stringType&);
    SDLDrawable* getDrawable(const stringType&);
    boolType removeDrawable(const stringType&);
    SDLDrawable* copyDrawable(const stringType&, const stringType&);

};

#endif //END SDLASSETMANAGER__HPP
