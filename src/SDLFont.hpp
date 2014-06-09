#ifndef SDLFONT__HPP
#define SDLFONT__HPP
//DESCRIPTION
/*
  Font representation for TTF_Font which is being wrapped to allow
  easier lua binding.
 */

//CLASSES
class SDLFont;

//INCLUDES
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS

//MACROS

//ENUM
enum class enumFontRenderType {
    SOLID,
    SHADED,
    BLENDED
};

enum class enumFontHintingType {
    NORMAL,
    LIGHT,
    MONO,
    NONE
};

//STRUCTS
struct FontStyle {
    boolType bBold;
    boolType bItalic;
    boolType bUnderline;
    boolType bStrikethrough;
};

struct GlyphMetrics {
    int minx;
    int maxx;
    int miny;
    int maxy;
    int advance;
};

struct TextSize {
    int w;
    int h;
};

struct FontColor {
    unsigned short r;
    unsigned short g;
    unsigned short b;
};

//TYPEDEFS

//FUNCTIONS

//BEGIN
class SDLFont {
private:
    TTF_Font* fontContext = nullptr;
    int fontSize;
    enumFontRenderType renderType = enumFontRenderType::SOLID;
    FontColor fontColor;
public:
    SDLFont();
    SDLFont(TTF_Font* fontContext, int fontSize);
    virtual ~SDLFont();
    
    int getFontSize();

    TTF_Font* getFontContext();

    FontColor getFontColor();
    void setFontColor(FontColor);

    enumFontRenderType getRenderType();
    void setRenderType(enumFontRenderType);

    FontStyle getStyle();
    void setStyle(FontStyle);

    //TTF_GetFontOutline
    int getOutline();
    void setOutline(int outline);

    enumFontHintingType getHinting();
    void setHinting(enumFontHintingType);

    boolType getKerning();
    void setKerning(boolType);
    
    int getMaxHeight();
    
    //more specific font functions
    int getAscent();
    int getDescent();
    int getLineSkip();
    
    //TTF FontFaceIsFixedWidth()
    boolType isMonospace();

    stringType getFamilyName();
    stringType getFamilyStyle();

    boolType hasGlyph(Uint16 ch);
    GlyphMetrics getGlyph(Uint16 ch);

    TextSize calculateTextSize(stringType text);

    SDLFont clone();

};

#endif //END SDLFONT__HPP
