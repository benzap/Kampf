#include "SDLFontManager.hpp"

SDLFont* SDLFontManager::addFont(stringType name,
				 const stringType& filename,
				 int fontSize) {
    assert(windowContext != nullptr);

    TTF_Font* fontContext = TTF_OpenFont(filename.c_str(), fontSize);

    if (fontContext == NULL) {
	std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    }

    SDLFont sdlFont = SDLFont(fontContext, fontSize);

    auto fontPair = std::pair<stringType, SDLFont> (name, sdlFont);
    fontContainer.insert(fontPair);

    return &fontContainer[name];
}
    
boolType SDLFontManager::hasFont(const stringType& name) {
    if (fontContainer.find(name) != fontContainer.end()) {
	return true;
    }
    return false;
}

SDLFont* SDLFontManager::getFont(const stringType& name) {
    return &fontContainer[name];
}

boolType SDLFontManager::removeFont(const stringType& name) {
    return fontContainer.erase(name);
}

SDLFont* SDLFontManager::copyFont(const stringType& srcName,
				  const stringType& destName) {
    assert(hasFont(srcName));
    
    SDLFont* font = this->getFont(srcName);
    SDLFont newFont = font->clone();
    
    auto fontPair = std::pair<stringType, SDLFont>(destName, newFont);
    fontContainer.insert(fontPair);
    
    return &fontContainer[destName];
}

void SDLFontManager::setWindowContext(SDLRenderWindow* windowContext) {
    this->windowContext = windowContext;
}
