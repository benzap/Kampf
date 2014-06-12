#include "SDLText.hpp"

SDLText::SDLText() : AbstractDrawable(SDL_TEXT) {
    
}

SDLText::SDLText(SDLRenderWindow* windowContext) : 
    AbstractDrawable(SDL_TEXT),
    windowContext(windowContext),
    sourceRectangle(new SDL_Rect()) {}

SDLText::~SDLText() {
    
}

int SDLText::draw(Vector3 position,
		  Quaternion orientation) {

    //if it's been modified recently, we need to re-generate our text texture
    if (!this->bRendered) {
	this->generateTextSequence();
    }

    //draw our texture
    auto viewport = this->windowContext->getViewport();
    floatType widthFactor = this->windowContext->getScaledWidthFactor();
    floatType heightFactor = this->windowContext->getScaledHeightFactor();
    
    auto textureWidth = sourceRectangle->w;
    auto textureHeight = sourceRectangle->h;

    SDL_Rect outputRect;
    outputRect.x = (position.x - viewport->x) * widthFactor;
    outputRect.y = (position.y - viewport->y) * heightFactor;
    outputRect.w = textureWidth * widthFactor;
    outputRect.h = textureHeight * heightFactor;

    // std::cout << "outputrect:" << outputRect.x << " ";
    // std::cout << outputRect.y << " ";
    // std::cout << outputRect.w << " ";
    // std::cout << outputRect.h << std::endl;	

    SDL_RenderCopy(windowContext->getRenderer(),
		   texture, 
		   this->sourceRectangle,
		   &outputRect);

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

void SDLText::appendText(stringType text, stringType fontname) {    
    TextToken textToken;
    textToken.text = text;
    
    
    if (fontname == "default" && this->defaultFont != nullptr) {
	textToken.font = this->defaultFont;
    }
    
    else {
	auto fontManager = SDLFontManager::getInstance();
	assert(fontManager->hasFont(fontname));
	textToken.font = fontManager->getFont(fontname);
    }
    
    this->textSequence.push_back(textToken);
    this->bRendered = false;
}

void SDLText::clearText() {
    if (this->textSequence.size() == 0) return;

    this->textSequence.clear();
    this->bRendered = false;
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
    for (auto token : this->textSequence) {
	auto font = token.font;
	auto text = token.text;
	
	//...
    }

    //TODO: do this correctly (testing)
    if (textSequence.size() > 0) {
	//just draw the first one
	auto token = this->textSequence[0];
	
	auto fontColor = token.font->getFontColor();

	SDL_Color color = {fontColor.r, fontColor.g, fontColor.b, fontColor.a};

	//delete old surface
	if (this->surface != nullptr) {
	    SDL_FreeSurface(this->surface);
	}

	//populate our surface, render it based on the type
	switch(token.font->getRenderType()) {
	case enumFontRenderType::SOLID:
	default:
	    this->surface = TTF_RenderText_Solid(token.font->getFontContext(),
						 token.text.c_str(),
						 color);
	    break;
	case enumFontRenderType::BLENDED:
	    this->surface = TTF_RenderText_Blended(token.font->getFontContext(),
						   token.text.c_str(),
						   color);
	    break;
	case enumFontRenderType::SHADED:
	    this->surface = TTF_RenderText_Shaded(token.font->getFontContext(),
						  token.text.c_str(),
						  {0,0,0,0},
						  color);
	    break;
	}


    }

    //delete old texture
    if (this->texture != nullptr) {
	SDL_DestroyTexture(this->texture);
    }

    //generate a new texture
    this->texture = SDL_CreateTextureFromSurface(windowContext->getRenderer(),
						 this->surface);

    auto textureSize = this->getSize();
    this->sourceRectangle->x = 0;
    this->sourceRectangle->y = 0;
    this->sourceRectangle->w = textureSize[0];
    this->sourceRectangle->h = textureSize[1];
    
    if (this->texture == NULL) {
	std::cerr << "Warning: unable to create texture from surface";
	std::cerr << std::endl;
	std::cerr << SDL_GetError() << std::endl;
    }

    this->bRendered = true;
}

void SDLText::redraw() {
    this->bRendered = false;
}
