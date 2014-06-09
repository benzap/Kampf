#include "SDLText.hpp"

SDLText::SDLText() : AbstractDrawable(SDL_TEXT) {
    
}

SDLText::SDLText(SDLRenderWindow* windowContext) : 
    AbstractDrawable(SDL_TEXT),
    windowContext(windowContext) {}

SDLText::~SDLText() {

}

int SDLText::draw(Vector3 position,
		  Quaternion orientation) {
    return 0;
}
 
void SDLText::setWindowContext(SDLRenderWindow* windowContext) {
    this->windowContext = windowContext;
}

std::vector<int> SDLText::getSize() {
    std::vector<int> textureSize = {
	surface->w, surface->h
    };

    return textureSize;
}

SDLText* SDLText::appendText(stringType text, stringType fontname) {
    auto fontManager = SDLFontManager::getInstance();
    assert(fontManager->hasFont(fontname));

    TextToken textToken;
    textToken.font = fontManager->getFont(fontname);
    textToken.text = text;
    
    this->textSequence.push_back(textToken);
}

void SDLText::clearText() {
    this->textSequence.clear();
}

integerType SDLText::getTextLength() {
    int length = 0;
    for (auto token : this->textSequence) {
	length +=  token.text.size();
    }
    return length;
}

textSequenceContainerType SDLText::getTextSequence() {
    return this->textSequence;
}

void SDLText::setDefaultFont(const stringType& name) {
    auto fontManager = SDLFontManager::getInstance();
    assert(fontManager->hasFont(name));    
    this->defaultFont = fontManager->getFont(name);
}

void SDLText::generateTextSequence() {
    
}

