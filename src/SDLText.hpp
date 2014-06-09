#ifndef SDLTEXT__HPP
#define SDLTEXT__HPP
//DESCRIPTION
/*
  Represents text on the screen, and inherits from abstractdrawable
  Each SDLText can consist of several fonts, which make up a textsequence
*/

//CLASSES
class SDLText;

//INCLUDES
#include <vector>
#include <cassert>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "AbstractDrawable.hpp"
#include "SDLRenderWindow.hpp"
#include "SDLFont.hpp"
#include "SDLFontManager.hpp"

//DEFINITIONS
#define SDL_TEXT "SDL_TEXT"

//MACROS

//STRUCTS

//Represents one token of text in a sequence of text
struct TextToken {
    SDLFont* font;
    stringType text;
};

//TYPEDEFS
typedef std::vector<TextToken> textSequenceContainerType;

//FUNCTIONS

//BEGIN
class SDLText : public AbstractDrawable {
private:
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;

    SDLRenderWindow* windowContext = nullptr;
    
    //This stores a sequence of fonts
    textSequenceContainerType textSequence;
    SDLFont* defaultFont = nullptr;
    SDL_Rect* sourceRectangle = nullptr;

    //A boolean that determines if the current text sequence should be
    //re-rendered or not. This is set to false everytime the current
    //text sequence is modified.
    boolType bRendered = false;
public:
    SDLText();
    SDLText(SDLRenderWindow* windowContext);
    virtual ~SDLText();

    virtual int draw(Vector3 position = Vector3(), 
		     Quaternion orientation = Quaternion());

    void setWindowContext(SDLRenderWindow*);

    std::vector<int> getSize();

    //text sequence functions
    void appendText(stringType text, stringType fontname = "default");
    void clearText();
    integerType getTextLength();
    textSequenceContainerType getTextSequence();
    

    //the default font
    void setDefaultFont(const stringType& name);

    //function to generate our texture
    void generateTextSequence();

};

#endif //END SDLTEXT__HPP
