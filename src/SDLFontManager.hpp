#ifndef SDLFONTMANAGER__HPP
#define SDLFONTMANAGER__HPP
//DESCRIPTION
/*
  This is used to store different fonts for referencing
 */

//CLASSES
class SDLFontManager;

//INCLUDES
#include <map>
#include <tuple>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "SDLRenderWindow.hpp"
#include "SDLFont.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::map<stringType, SDLFont> fontContainerType;

//FUNCTIONS

//BEGIN
class SDLFontManager {
private:
    SDLFontManager() {}
    SDLFontManager(SDLFontManager const&);
    void operator=(SDLFontManager const&);

    fontContainerType fontContainer;
public:
    static SDLFontManager* getInstance() {
	static SDLFontManager _instance = SDLFontManager();
	return &_instance;
    }
    
    SDLFont* addFont(stringType name,
		     const stringType& filename);
    
    boolType hasFont(const stringType&);
    SDLFont* getFont(const stringType&);
    boolType removeFont(const stringType&);
    SDLFont* copyFont(const stringType&, const stringType&);

};

#endif //END SDLFONTMANAGER__HPP
