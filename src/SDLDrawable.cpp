#include "SDLDrawable.hpp"

SDLDrawable::SDLDrawable(SDL_Texture* texture) :
    AbstractDrawable("SDL"),
    texture(texture) {
    auto textureSize = this->getTextureSize();
    this->sourceRectangle = new SDL_Rect();
    this->sourceRectangle->w = textureSize[0];
    this->sourceRectangle->h = textureSize[1];
}

SDLDrawable::~SDLDrawable() { 
    SDL_DestroyTexture(texture);
    delete sourceRectangle;
}

int SDLDrawable::draw(Vector3 position, 
		      Quaternion orientation) {
    SDL_RenderCopy(windowContext->getRenderer(), texture, NULL, NULL);
}

void SDLDrawable::setRect(SDL_Rect* rect) {
    *this->sourceRectangle = *rect;
}

void SDLDrawable::setRect(integerType x, integerType y, 
			  integerType w, integerType h) {
    
}

const SDL_Rect* SDLDrawable::getRect() {
    return sourceRectangle;
}

void SDLDrawable::setWindowContext(SDLRenderWindow* windowContext) {
    this->windowContext = windowContext;
}

std::vector<int> SDLDrawable::getTextureSize() {
    int* textureWidth;
    int* textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, textureWidth, textureHeight);

    std::vector<int> textureSize = {
	*textureWidth, *textureHeight 
    };
    
    return textureSize;
}
