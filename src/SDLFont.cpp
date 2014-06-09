#include "SDLFont.hpp"

SDLFont::SDLFont(TTF_Font* fontContext, int fontSize) :
    fontContext(fontContext),
    fontSize(fontSize) {
    
}

SDLFont::~SDLFont() {

}

    
int SDLFont::getFontSize() {
    return this->fontSize;
}


TTF_Font* SDLFont::getFontContext() {
    return this->fontContext;
}


FontColor SDLFont::getFontColor() {
    return this->fontColor;
}

void SDLFont::setFontColor(FontColor fontColor) {
    this->fontColor = fontColor;
}


enumFontRenderType SDLFont::getRenderType() {
    return this->renderType;
}

void SDLFont::setRenderType(enumFontRenderType type) {
    this->renderType = type;
}


FontStyle SDLFont::getStyle() {
    int styleMask = TTF_GetFontStyle(this->fontContext);
    FontStyle fontStyle;
    fontStyle.bBold = (styleMask & TTF_STYLE_BOLD) ? true : false;
    fontStyle.bItalic = (styleMask & TTF_STYLE_ITALIC) ? true : false;
    fontStyle.bUnderline = (styleMask & TTF_STYLE_UNDERLINE) ? true : false;
    fontStyle.bStrikethrough = (styleMask & TTF_STYLE_STRIKETHROUGH) ? true : false;
    
    return fontStyle;
}

void SDLFont::setStyle(FontStyle style) {
    int styleMask = TTF_STYLE_NORMAL;
    if (style.bBold) {
	styleMask |= TTF_STYLE_BOLD;
    }
    if (style.bItalic) {
	styleMask |= TTF_STYLE_ITALIC;
    }
    if (style.bUnderline) {
	styleMask |= TTF_STYLE_UNDERLINE;
    }
    if (style.bStrikethrough) {
	styleMask |= TTF_STYLE_STRIKETHROUGH;
    }
    TTF_SetFontStyle(this->fontContext, styleMask);
}


//TTF_GetFontOutline
int SDLFont::getOutline() {
    return TTF_GetFontOutline(this->fontContext);
}

void SDLFont::setOutline(int outline) {
    TTF_SetFontOutline(this->fontContext, outline);
}


enumFontHintingType SDLFont::getHinting() {
    int hintingNum = TTF_GetFontHinting(this->fontContext);
    switch(hintingNum) {
    case TTF_HINTING_NONE:
	return enumFontHintingType::NONE;
    case TTF_HINTING_MONO:
	return enumFontHintingType::MONO;
    case TTF_HINTING_LIGHT:
	return enumFontHintingType::LIGHT;
    case TTF_HINTING_NORMAL:
    default:
	return enumFontHintingType::NORMAL;
    }
}

void SDLFont::setHinting(enumFontHintingType hinting) {
    int hintingNum = TTF_HINTING_NORMAL;
    switch(hinting) {
    case enumFontHintingType::NONE:
	hintingNum = TTF_HINTING_NONE;
	break;
    case enumFontHintingType::NORMAL:
	hintingNum = TTF_HINTING_NORMAL;
    case enumFontHintingType::LIGHT:
	hintingNum = TTF_HINTING_LIGHT;
    case enumFontHintingType::MONO:
	hintingNum = TTF_HINTING_MONO;
    }
    TTF_SetFontHinting(this->fontContext, hintingNum);
}


boolType SDLFont::getKerning() {
    int kerning = TTF_GetFontKerning(this->fontContext);
    return (kerning > 0) ? true : false;
}

void SDLFont::setKerning(boolType bKerning) {
    int kerning = (bKerning) ? 1 : 0;
    TTF_SetFontKerning(this->fontContext, kerning);
}

    
int SDLFont::getMaxHeight() {
    return TTF_FontHeight(this->fontContext);
}

    
//more specific font functions
int SDLFont::getAscent() {
    return TTF_FontAscent(this->fontContext);
}

int SDLFont::getDescent() {
    return TTF_FontDescent(this->fontContext);
}

int SDLFont::getLineSkip() {
    return TTF_FontLineSkip(this->fontContext);
}

    
//TTF FontFaceIsFixedWidth()
boolType SDLFont::isMonospace() {
    int isMonospace = TTF_FontFaceIsFixedWidth(this->fontContext);
    return (isMonospace > 0) ? true : false;
}


stringType SDLFont::getFamilyName() {
    char* fontFamily = TTF_FontFaceFamilyName(this->fontContext);
    if (fontFamily != NULL) {
	stringType fontFamilyString = stringType(fontFamily);
	return fontFamilyString;
    }
    else {
	return "None";
    }
}

stringType SDLFont::getFamilyStyle() {
    char * fontStyle = TTF_FontFaceStyleName(this->fontContext);
    if (fontStyle != NULL) {
	stringType fontStyleString = stringType(fontStyle);
	return fontStyle;
    }
    else {
	return "None";
    }
}


boolType SDLFont::hasGlyph(Uint16 ch) {
    int isProvided = TTF_GlyphIsProvided(this->fontContext, ch);
    return (isProvided > 0) ? true : false;
}

GlyphMetrics SDLFont::getGlyph(Uint16 ch) {
    GlyphMetrics metrics;
    int minx, miny, maxx, maxy, advance;
    int error = TTF_GlyphMetrics(this->fontContext, ch,
				 &minx, &maxx,
				 &miny, &maxy,
				 &advance);

    metrics.minx = minx;
    metrics.miny = miny;
    metrics.maxx = maxx;
    metrics.maxy = maxy;
    metrics.advance = advance;
    
    return metrics;
}


TextSize SDLFont::calculateTextSize(stringType text) {
    TextSize textSize;
    int w, h;
    int error = TTF_SizeText(this->fontContext, text.c_str(),
			     &w, &h);
    textSize.w = w;
    textSize.h = h;

    return textSize;
}
