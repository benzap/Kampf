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
    SDLFontManager() {
	//check if we've intialized here

	if(!TTF_WasInit() && TTF_Init()==-1) {
	    std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
	    exit(1);
	}
	
    }
    SDLFontManager(SDLFontManager const&);
    void operator=(SDLFontManager const&);

    fontContainerType fontContainer;

    SDLRenderWindow* windowContext;
public:
    static SDLFontManager* getInstance() {
	static SDLFontManager _instance = SDLFontManager();
	return &_instance;
    }
    
    SDLFont* addFont(stringType name,
		     const stringType& filename,
		     int fontSize);
    
    boolType hasFont(const stringType&);
    SDLFont* getFont(const stringType&);
    boolType removeFont(const stringType&);
    SDLFont* copyFont(const stringType&, const stringType&);

    void setWindowContext(SDLRenderWindow*);

};

#endif //END SDLFONTMANAGER__HPP
